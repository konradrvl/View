import { Component, Input, OnInit } from '@angular/core';
import { MatSnackBar } from '@angular/material';
import { Floor } from '../../models/floor';
import { RoomService } from '../../services/Room/room.service';
import { WebsocketService } from '../../services/Websocket/websocket.service';

@Component({
  selector: 'app-roomlist',
  templateUrl: './roomlist.component.html',
  styleUrls: ['./roomlist.component.css']
})
export class RoomlistComponent implements OnInit {

  @Input() floor: Floor;
  private _roomElements: Element[];

  constructor(private snackBar: MatSnackBar,
    private websocketService: WebsocketService, private roomService: RoomService) {
  }

  async ngOnInit() {
    try {
      this._roomElements = (await this.roomService.getRooms(this.floor.id))
        .map(x => new Element(x.id, x.name, `./floors/${this.floor.id}/rooms/${x.id}`, -1, x.maxPersonCount));
      for (const element of this._roomElements) {
        this.websocketService.subscribe(element.id, x => element.personCount = x);
      }
    } catch (e) {
      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });
    }
  }

  public get roomElements() {
    return this._roomElements
  }

}

export class Element {
  constructor(
    public id: number,
    public name: string,
    public link: string,
    public personCount: number,
    public maxPersonCount: number
  ) {
  }
}
