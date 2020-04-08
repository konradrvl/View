# Webapplikation

## Komponenten

### Login

In der `ngOnInit()` Methode der Login Komponente wird als erstes eine Form mit Validators instanziiert, um die Nutzereingaben zu validieren.

**login.component.ts**

``` Typescript
 ngOnInit() {
    this._form = this.formBuilder.group({
      username: ['', Validators.required],
      password: ['', Validators.required],
      keepLoggedIn: [false]
    });
  }
```

Durch einen Klick auf den Submit-Button wird die `onSubmit()` Methode ausgeführt. In dieser Methode werden die Nutzereingaben an den Server versandt, auf dessen Ergebnis gewartet und entsprechend weitere Schritte eingeleitet. Die Variable `returnUrl` dient dabei der Navigation zurück auf eine Seite auf die der Nutzer zugreifen wollte, während seine Session abgelaufen ist.

**login.component.ts**

``` Typescript
async onSubmit() {

    if (this.form.invalid) {
      return;
    }

    this._loading = true;

    try {

      await this.authenticationService.login(this.form.username.value, this.form.password.value, this.form.keepLoggedIn.value);

      this.snackBar.open(`Logged in as ${this.form.username.value}!`, 'OK', { duration: 4000 });

      const returnUrl = this.route.snapshot.queryParams['returnUrl'];
      if (returnUrl) {
        this.router.navigate([returnUrl]);
      } else {
        this.router.navigate(['view/home']);
      }

    } catch (e) {

      this._loading = false;
      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }
```

### Navigation

Das Menü ist während der gesamten Bedienung der Anwendung omnipräsent. Der aktuelle Status des Menüs wird über die aktuelle Url bestimmt und der Inhalt entsprechend angepasst.

**nav-content.component.ts**

``` Typescript
private handleUrl(url: string) {

    const urlArr = url.match('(buildings|floors|rooms)/(\\d*)');

    if (urlArr) {
      if (urlArr[1] === 'buildings') {
        this.showFloors(+urlArr[2]);
        return;
      }
      if (urlArr[1] === 'floors') {
        this.showRooms(+urlArr[2]);
        return;
      }
      if (urlArr[1] === 'rooms') {
        this.showRoom(+urlArr[2])
        return;
      }
    }
    this.showBuildings()
  }
```

Nach aufrufen einer `show...()` Methode wird der Inhalt des Menüs(Gebäude, Stockwerke, Räume) vom Server angefordert und aktualisiert.

**nav-content.component.ts**

``` Typescript
private async showBuildings() {

    this._loading = true;

    try {

      const buildings = await this.buildingService.getBuildings();

      this._title = new Element('Buildings', undefined);

      this._elements = buildings.map(x => new Element(x.name, `./buildings/${x.id}`));
      this._icon = 'home';

      this._add = new Element('Add Building', './building/add');

      this._loading = false;
      this._error = false;

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });
      this._loading = false;
      this._error = true;

    }
  }
```

### Building

Die Daten des Gebäudes werden über die ID in der URL abgefragt. Mithilfe der abgefragten Stockwerke wird dann im HTML File eine Liste der Stockwerke erstellt. Dort wird für jedes Stockwerk die Unterkomponente Roomlist aufgerufen.

**building.component.html**

``` HTML
<mat-card class="floor-card" *ngFor="let element of elements">
  <mat-card-content>
    <mat-toolbar color="primary">{{element.name}}</mat-toolbar>
    <app-roomlist [floor]="element"></app-roomlist>
  </mat-card-content>
</mat-card>
```

### Roomlist

**roomlist.component.ts**
Wie oben beschrieben, bekommt die Roomlist Komponente den jeweiligen Floor als Input Wert. Mit diesem fragt sie alle Räume des Stockwerks ab und registriert sich für Updates zu Änderungen der Belegungen.
#### 
``` Typescript
{
      this._roomElements = (await this.roomService.getRooms(this.floor.id))
        .map(x => new Element(x.id, x.name, `./floors/${this.floor.id}/rooms/${x.id}`, -1, x.maxPersonCount));
      for (const element of this._roomElements) {
        this.websocketService.subscribe(element.id, x => element.personCount = x);
      }
}
```

### Heatmap

Die Heatmap ist das Element der Stockwerke, welches einen strukturierten Aufbau des Stockwerks anzeigt. Dabei gibt es zwei verschiedene Komponenten. Die "normale" Heatmap, die hier beschrieben wird, bietet lediglich lesenden Zugriff und zeigt dem User farblich an, wie viele Personen sich in einem Raum befinden. Mithilfe der Edit-Komponente, die weiter unten dokumentiert ist, lässt sich die Anordnung der Räume verändern.

Daten, welche von der Komponente benötigt werden, werden in der `ngOnInit` Methode vom Server abgefragt.

**heatmap.component.ts**

``` Typescript
async ngOnInit() {

  const id = +this.route.snapshot.paramMap.get('id');
  this.floor = await this.floorService.getFloor(id);
  const rooms = await this.roomService.getRooms(this.floor.id);

  this._elements = rooms.map(x => this.mapToHeatmap(x));
  for (const element of this._elements) {
    this.websocketService.subscribe(element.id, x => element.personCount = x);
  }
}
```

Die Farben der Elemente innerhalb der Heatmap werden mithilfe der `calculateColor()` Methode berechnet.
Die Parameter können folgendermaßen erklärt werden:

* `first`: Startwert für Farbverlauf
* `second`: Endwert für Farbverlauf
* `curr`: aktuelle Anzahl an Personen
* `max`: maximale Personenanzahl des Raums

**heatmap.component.ts**

``` Typescript
  private calculateColor(first: number, second: number, curr: number, max: number) {
    const diff = Math.abs(first - second);
    const perc = curr / max;
    return first > second ? (second + (diff - diff * perc)) : (first + (diff - diff * perc));
  }
```

### Edit-Heatmap


Da Edit-Heatmap immer als verschachtelte Komponente eingebunden wird (in der Add-Room Komponente und Edit-Floor Komponente), muss sie sich nicht um die Datenbeschaffung kümmern. Die Raumdaten werden mittels eines Inputs an die Komponente übergeben. Sobald der User Räume verschiebt bzw. vergrößert/verkleinert, wird der Raum mit den Änderungen in ein neues Array (`modifiedRooms`) von Räumen gepusht. Wenn der Nutzer in der übergeordneten Komponente den Save/Edit Button bestätigt, wird die Methode `getRooms()` aufgerufen und das `modifiedRooms` Array an die Komponente übergeben, die sich dann um die weitere Verarbeitung kümmert.
Die Methode `dragged(event, room: Room)` wird ausgeführt sobald der Raum verschoben wurde. Der Parameter `event` beinhaltet dann die geänderten Werte des Raumes, `room` spiegelt den ursprünglichen Raum wieder.

**edit-heatmap.component.ts**

``` Typescript
  dragged(event, room: Room) {

    const modifiedRoom: Room = this.modifiedRooms.find(x => x.id === room.id);
    if (modifiedRoom) {
      modifiedRoom.posX = Math.round(room.posX + event.x);
      modifiedRoom.posY = Math.round(room.posY + event.y);
    } else {
      this.modifiedRooms.push(new Room(
        room.name,
        room.maxPersonCount,
        room.floorId,
        room.posX + Math.round(event.x),
        room.posY + Math.round(event.y),
        room.width,
        room.height,
        room.id,
        room.iotDeviceId
      ));
    }
  }
```

Falls der Raum schon einmal verändert wurde, werden nur die Werte `posX` und `posY` des Objekts verändert. Ansonsten wird der Raum mit den Stammdaten sowie den neuen Positionen in das Array gepusht.

Die Methode `resized(event, room: Room)` verfährt analog zu der `dragged()` Methode, mit dem Unterschied, dass statt der X und Y Position die `height` und `width` Werte verändert werden.

### Chart

Das Chart ist mithilfe der Bibliothek `chart.js` implementiert. In der Methode `getOccupations()` werden die Belegungsdaten der letzten 24 Stunden vom Server abgefragt. Anschließend werden die Daten in Personenanzahl und den jeweiligen Datumsstempeln aufgeteilt um sie den Achsen des Graphen zuordnen zu können. Bevor der Chart erstellt wird, müssen die Daten noch bereinigt werden. Falls eine Personenanzahl < 0 vorliegt, wird die Anzahl auf 1 gesetzt und die Farbe des Balkens auf grau. Ist der Wert valide, behält er den Wert und hat eine hellblaue Farbe.

**chart.component.ts**

``` Typescript
    this.chart = new Chart('chart', {
      type: 'bar',
      data: {
        labels: this._dates,
        datasets: [
          {
            data: clearedData,
            borderColor: colours,
            backgroundColor: colours,
            pointBackgroundColor: 'rgba(48, 63, 159, 1)',
            pointHoverBackgroundColor: 'rgba(48, 63, 159, 1)',
            pointHoverBorderColor: 'rgba(48, 63, 159, 0.6)',
            pointHoverBorderWidth: 6,
            borderWidth: 3,
          }
        ]
      },
      options: {
        legend: {
          display: false
        },
        scales: {
          xAxes: [{
            display: true,
          },
          ],
          yAxes: [{
            display: true,
          }],
        }
      }
    });
```

## Services

### Websocket

In diesem Zusammenhang wird vorausgesetzt, dass sobald ein User das erste mal Live Daten eines/mehrerer Räume anfordert, eine Websocket Verbindung aufgebaut wird. Diese besteht solange die Applikation geöffnet ist.

In der `subscribe` Methode wird ein Wunsch auf Live Daten an den Server gesendet. Danach wird mithilfe der `roomID` und einem Callback eine neue Regel erstellt, in welchen Fall und wohin Daten übergeben werden. Anschließend wird die `roomID` zur Subscriptionliste hinzugefügt.

**websocket.service.ts**

``` Typescript
  public subscribe(roomId: number, cb: (value: number) => void) {
    this.webSocket.send(JSON.stringify([roomId]));
    this.subject.pipe(filter(x => x.roomId === roomId || x.roomId === 0)).subscribe(x => cb(x.personCount));
    this._subscriptions.add(roomId);
  }
```

Bei Initialisierung der `onmessage` Methode des Websockets, wird festgelegt, dass jede Message in die `next` Methode des Objekts `subject` gepusht wird.

**websocket.service.ts**

``` Typescript
this.webSocket.onmessage = msg => {
  const data = JSON.parse(msg.data);
  if (isMessage(data)) {
    this.subject.next({ roomId: data.roomId, personCount: data.personCount });
  }
};
```

### RoomService

Stellt den Service zur Datenabfrage der Räume dar. Folgende Funktionen werden angeboten:

* `getRoom (roomId: number)`: Mittels einer `roomID` kann ein Raum Objekt vom Server abgefragt werden.
* `getRooms(floorId: number)`: Mittels einer `floorID` werden alle Räume eines Stockwerks abgefragt und als Array von Räumen zurückgegeben.
* `createRoom(newRoom: Room)`: Ein Raum Objekt wird an den Server gesendet. Zurückgegeben wird das Raum Objekt wie es dann in der Datenbank liegt. Also mit generierter roomID.
* `editRoom(roomId: number, newRoom: Room)`: Mithilfe einer vorhandenen `roomID` und eines neuen Raumes, kann der Raum hinter einer ID ersetzt werden.
* `deleteRoom(roomId: number)`: Mittels der `roomID` kann ein Raum gelöscht werden. Die Historie des Raumes also die Personenanzahl wird dabei auch gelöscht!
* `getRoomHistory(roomId: number, from: Date, to: Date)`: Mit `roomID`, `from` und `to` kann ein Zeitraum festgelegt werden, in der eine Historie eines Raums abgefragt werden soll. Das Datumsformat sollte dabei in ISO Format sein. Zurückgeliefert wird ein Array von `Occupation`, welche aus einem Array von Personenzahlen und Datumstempeln besteht.

Anhand dieses Services lassen sich auch der Service von Gebäuden und Stockwerken erklären, da diese sehr ähnlich aufgebaut sind und ähnliche Methoden haben.

### AuthService

Bietet den Service an um Nutzer einzuloggen bzw. zu registrieren. Die Basis URL auf der alle API anfragen ankommen lautet `/api/user`

**authentication.service.ts**

``` Typescript
  public async login(username: string, password: string, keepLoggedIn: boolean) {
    await this.http.post(AuthenticationService.URL, { username, password, keepLoggedIn }).toPromise();
  }

  public async register(username: string, password: string) {
    await this.http.post(`${AuthenticationService.URL}/register`, { username, password }).toPromise();
  }

  public async isLoggedin() {
    try {
      await this.http.get(`${AuthenticationService.URL}/check`).toPromise();
      return true;
    } catch (e) {
      console.log(e);
      return false;
    }
  }
```

Hauptsächlich werden hier lediglich Anfragen auf die API ausgeführt. Beim Login gibt es die Zusatzoption `keepLoggedIn`, die einen Cookie zurückliefert, der länger gültig ist.

## Other

### AuthGuard

Der AutheticationGuard greift auf alle Komponenten zu, welche hinter der `Login` bzw. `Register` Komponente liegen und prüft dabei ob der Nutzer berechtigt ist diese zu sehen. Dazu ruft er die Methode `isLoggedIn()` aus dem `authenticationService` auf. Hat der Nutzer vorher eine Ressource zugegriffen die jetzt nicht mehr verfügbar ist (Bspw. weil sein Cookie abgelaufen ist), fügt der AuthenticationGuard diesen Parameter als QueryParameter an die URL an, um ihn nach dem Login wieder weiterleiten zu können.