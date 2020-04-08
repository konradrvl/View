import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Floor, isFloor, isFloorArray } from '../../models/floor';

@Injectable({
  providedIn: 'root'
})
export class FloorService {

  private static readonly URL: string = '/api/floors';

  constructor(private http: HttpClient) { }

  public async getFloor(floorId: number): Promise<Floor> {

    const res = await this.http.get(`${FloorService.URL}/${floorId}`).toPromise();

    if (isFloor(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async getFloors(buildingId: number): Promise<Floor[]> {

    const res = await this.http.get(`${FloorService.URL}`, { params: { 'buildingId': `${buildingId}` } }).toPromise();

    if (isFloorArray(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async createFloor(newFloor: Floor): Promise<Floor> {

    const res = await this.http.post(`${FloorService.URL}`, newFloor).toPromise();

    if (isFloor(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async editFloor(floorId: number, newFloor: Floor): Promise<Floor> {

    const res = await this.http.put(`${FloorService.URL}/${floorId}`, newFloor).toPromise();

    if (isFloor(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async deleteFloor(floorId: number) {

    await this.http.delete(`${FloorService.URL}/${floorId}`).toPromise();

  }
}
