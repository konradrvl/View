import { Component, OnInit } from '@angular/core';
import { DataService } from '../service/data.service';
import { MatSnackBar, MatIconRegistry } from '@angular/material';
import { DomSanitizer } from '@angular/platform-browser';
import { Status } from './wifi.status';
import { Wifi } from '../service/wifi.model';


@Component({
  selector: 'app-wifi',
  templateUrl: './wifi.component.html',
  styleUrls: ['./wifi.component.css']
})
export class WifiComponent implements OnInit {

    public selection: Wifi;
    public password: string;
    public networks: Wifi[];
    public error: string;
    public status: Status = Status.pending;

  constructor(iconRegistry: MatIconRegistry, sanitizer: DomSanitizer, public dataService: DataService, public snackBar: MatSnackBar) {
    iconRegistry.addSvgIcon('wifi-1', sanitizer.bypassSecurityTrustResourceUrl('assets/icons/wifi-1.svg'));
    iconRegistry.addSvgIcon('wifi-1-locked', sanitizer.bypassSecurityTrustResourceUrl('assets/icons/wifi-1-locked.svg'));
    iconRegistry.addSvgIcon('wifi-2', sanitizer.bypassSecurityTrustResourceUrl('assets/icons/wifi-2.svg'));
    iconRegistry.addSvgIcon('wifi-2-locked', sanitizer.bypassSecurityTrustResourceUrl('assets/icons/wifi-2-locked.svg'));
    iconRegistry.addSvgIcon('wifi-3', sanitizer.bypassSecurityTrustResourceUrl('assets/icons/wifi-3.svg'));
    iconRegistry.addSvgIcon('wifi-3-locked', sanitizer.bypassSecurityTrustResourceUrl('assets/icons/wifi-3-locked.svg'));
    iconRegistry.addSvgIcon('wifi-4', sanitizer.bypassSecurityTrustResourceUrl('assets/icons/wifi-4.svg'));
    iconRegistry.addSvgIcon('wifi-4-locked', sanitizer.bypassSecurityTrustResourceUrl('assets/icons/wifi-4-locked.svg'));
    iconRegistry.addSvgIcon('reload', sanitizer.bypassSecurityTrustResourceUrl('assets/icons/reload.svg'));
    iconRegistry.addSvgIcon('warn', sanitizer.bypassSecurityTrustResourceUrl('assets/icons/warn.svg'));
  }

  ngOnInit() {
    this.searchForNetworks();
  }

  searchForNetworks(){
    this.status = Status.pending;
    this.dataService.searchForNetworks((wifis, err) => {
      if (err) {
        this.status = Status.error;
        this.error = err;
      } else {
        this.status = Status.success;
        this.networks = wifis;
      }
    });
  }

  submit(network: Wifi, password: string) {
    this.snackBar.open('Connecting to ' + network.ssid, 'Okey' ,
    {
      duration: 5000,
    });
    this.dataService.sendData(network.ssid, password);
  }


}
