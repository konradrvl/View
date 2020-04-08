# WiFi-Fronted

## Komponenten

### WiFi

In der `ngOnInit()` Methode der WiFi Komponente wird die `searchForNetworks()` Methode aufgerufen, in der Netzwerke in der Umgebung gescannt werden.

**wifi.component.ts**

``` Typescript
ngOnInit() {
    this.searchForNetworks();
}
```

**wifi.component.ts**

``` Typescript
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
```

In der `submit()` Methode der WiFi Komponente werden die Daten aus der Oberfläche an den Server gesendet.

**wifi.component.ts**

``` Typescript
submit(network: Wifi, password: string) {
  this.snackBar.open('Connecting to ' + network.ssid, 'Okey' ,
  {
    duration: 5000,
  });
  this.dataService.sendData(network.ssid, password);
}
```

## Services

### Dataservice

Die `searchForNetworks()` Methode des Dataservices ist dafür verantwortlich die verfügbaren Wlan Netzwerke vom IoT-Device
per WebAPI abzufragen und per Callback an die Oberfläche zu liefern.

**data.service.ts**

``` Typescript
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
```

Die `sendData(ssid, passwd)` Methode sendet dem IoT-Device per WebAPI das gewünschte Netzwerk und
das dazugehörige Passwort.

**data.service.ts**

``` Typescript
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
```