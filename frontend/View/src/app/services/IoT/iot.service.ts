import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { IoTDevice, isIoTDevice } from '../../models/ioTDevice';

@Injectable({
  providedIn: 'root'
})
export class IotService {

  private static readonly URL: string = '/api/iotDevices';

  constructor(private http: HttpClient) { }

  public async getIoTDevices(): Promise<string[]> {

    const res = await this.http.get(`${IotService.URL}/unused`).toPromise();

    if (Array.isArray(res)) {
      for (const e of res) {
        if (typeof e !== 'string') {
          throw new Error('Invalid response');
        }
      }
      return res;
    }

    throw new Error('Invalid response');
  }

  public async setIoTDevice(id: string): Promise<IoTDevice> {

    const res = await this.http.put(`${IotService.URL}/${id}`, {}).toPromise();

    if (isIoTDevice(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }
}
