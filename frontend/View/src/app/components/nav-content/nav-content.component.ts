import { Component, OnInit } from '@angular/core';
import { MatSnackBar } from '@angular/material';
import { NavigationEnd, Router } from '@angular/router';
import { BuildingService } from '../../services/Building/building.service';
import { FloorService } from '../../services/Floor/floor.service';
import { RoomService } from '../../services/Room/room.service';

@Component({
  selector: 'app-nav-content',
  templateUrl: './nav-content.component.html',
  styleUrls: ['./nav-content.component.css']
})
export class NavContentComponent implements OnInit {

  private _loading = false;
  private _error = false;

  private _title: Element;

  private _elements: Element[] = [];
  private _icon = '';

  private _add: Element;

  constructor(
    private snackBar: MatSnackBar,
    private router: Router,
    private buildingService: BuildingService,
    private floorService: FloorService,
    private roomService: RoomService,
  ) { }

  ngOnInit() {
    const url = this.router.url;
    this.handleUrl(url);

    this.router.events.subscribe(x => {
      if (x instanceof NavigationEnd) {
        this.handleUrl(x.urlAfterRedirects);
      }
    })
  }

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

  private async showFloors(buildingId: number) {

    this._loading = true;

    try {

      const floors = await this.floorService.getFloors(buildingId);

      this._title = new Element('Building', `./home`);

      this._elements = floors.map(x => new Element(x.name, `./floors/${x.id}`));
      this._icon = 'layers';

      this._add = new Element('Add Floor', `./buildings/${buildingId}/add`);

      this._loading = false;
      this._error = false;

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });
      this._loading = false;
      this._error = true;

    }
  }

  private async showRooms(floorId: number) {

    this._loading = true;

    try {

      const rooms = await this.roomService.getRooms(floorId);
      const floor = await this.floorService.getFloor(floorId);

      this._title = new Element('Floor', `./buildings/${floor.buildingId}`);

      this._elements = rooms.map(x => new Element(x.name, `./rooms/${x.id}`));
      this._icon = 'view_compact';

      this._add = new Element('Add Room', `./floors/${floorId}/add`);

      this._loading = false;
      this._error = false;

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });
      this._loading = false;
      this._error = true;

    }
  }

  private async showRoom(roomId: number) {

    this._loading = true;

    try {

      const room = await this.roomService.getRoom(roomId);
      const floorId = room.floorId;

      const rooms = await this.roomService.getRooms(floorId);

      this._title = new Element('Room', `./floors/${room.floorId}`);

      this._elements = rooms.map(x => new Element(x.name, `./rooms/${x.id}`));
      this._icon = 'view_compact';

      this._add = new Element('Add Room', `./floors/${floorId}/add`);

      this._loading = false;
      this._error = false;

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });
      this._loading = false;
      this._error = true;

    }
  }

  public get title() {
    return this._title;
  }

  public get elements() {
    return this._elements;
  }

  public get icon() {
    return this._icon;
  }

  public get add() {
    return this._add;
  }

  public get loading() {
    return this._loading;
  }

  public get error() {
    return this._error;
  }

}

export class Element {
  constructor(
    public name: string,
    public link: string) { };
}

export enum State {
  other,
  building,
  floor,
  room
}

export class History {
  public buildingId: number;
  public floorId: number;
  public roomId: number;
}

