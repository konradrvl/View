import { Injectable } from '@angular/core';
import { HttpClient, HttpParams } from '@angular/common/http';
import { Wifi } from './wifi.model';

@Injectable({ providedIn: 'root' })
export class DataService {

  public networks: Wifi[] = [];

  constructor(private http: HttpClient) { }

  public searchForNetworks(done: (networks: Wifi[], err?: string) => void): void {
    this.http.get('/api/wifi').subscribe(result => {
      const networks: Wifi[] = [];
      Array.prototype.push.apply(networks, result);
      done(networks);
    }, error => {
      let errorMsg: string = "Unknow Error";

      if (error.error) {
        switch (error.error.text) {
          case 'wifiInterfaceBusy':
            errorMsg = "The Wifi Interface is busy";
            break;
        }
      }

      done([], errorMsg);
    });
  }

  public sendData(ssid: string, passwd: string): void {
    const params = new HttpParams()
      .set("ssid", ssid)
      .set("passwd", passwd);

    this.http.put('/api/wifi', { params }).subscribe(x => {
      console.log(x);
    }, e => {
      console.log(e);
    });
  };

}
