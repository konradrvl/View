import { Component, OnInit } from '@angular/core';
import { MatSnackBar } from '@angular/material';
import { ActivatedRoute, Router } from '@angular/router';
import { Floor } from '../../models/floor';
import { Room } from '../../models/room';
import { FloorService } from '../../services/Floor/floor.service';
import { RoomService } from '../../services/Room/room.service';
import { WebsocketService } from '../../services/Websocket/websocket.service';

@Component({
  selector: 'app-heatmap',
  templateUrl: './heatmap.component.html',
  styleUrls: ['./heatmap.component.css']
})
export class HeatmapComponent implements OnInit {

  private floor: Floor;
  private _elements: RoomHeatmapElement[];

  constructor(private router: Router,
    private route: ActivatedRoute,
    private snackBar: MatSnackBar,
    private websocketService: WebsocketService,
    private floorService: FloorService,
    private roomService: RoomService) { }

  async ngOnInit() {

    const id = +this.route.snapshot.paramMap.get('id');
    this.floor = await this.floorService.getFloor(id);
    const rooms = await this.roomService.getRooms(this.floor.id);

    this._elements = rooms.map(x => this.mapToHeatmap(x));
    for (const element of this._elements) {
      this.websocketService.subscribe(element.id, x => element.personCount = x);
    }
  }

  public getColor(personCount: number, maxPersonCount: number) {

    const Blue = {
      r: 63,
      g: 81,
      b: 181
    };
    const Grey = {
      r: 158,
      g: 158,
      b: 158
    };

    if (personCount <= 0) {
      return `rgb(${Grey.r},${Grey.g},${Grey.b})`;
    }
    if (personCount >= maxPersonCount) {
      return `rgb(${Blue.r},${Blue.g},${Blue.b})`;
    }

    const color = `rgb(${this.calculateColor(Grey.r, Blue.r, personCount, maxPersonCount)},
    ${this.calculateColor(Grey.g, Blue.g, personCount, maxPersonCount)},
    ${this.calculateColor(Grey.b, Blue.b, personCount, maxPersonCount)})`;

    return color;

  }

  private calculateColor(first: number, second: number, curr: number, max: number) {
    const diff = Math.abs(first - second);
    const perc = curr / max;
    return first > second ? (second + (diff - diff * perc)) : (first + (diff - diff * perc));
  }


  private mapToHeatmap(room: Room): RoomHeatmapElement {
    return new RoomHeatmapElement(
      room.id,
      room.name,
      room.name,
      room.maxPersonCount,
      room.posX,
      room.posY,
      room.width,
      room.height,
    );
  }

  public edit() {
    this.router.navigate([`view/floors/${this.floor.id}/edit`]);
  }

  public async delete() {
    try {

      await this.floorService.deleteFloor(this.floor.id);

      this.snackBar.open(`${this.floor.name} deleted!`, 'OK', { duration: 4000 });
      this.router.navigate([`view/buildings/${this.floor.buildingId}`]);

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }

  public get elements() {
    return this._elements;
  }


}

export class RoomHeatmapElement {
  public personCount = -1;

  constructor(
    public id: number,
    public name: string,
    public link: string,
    public maxPersonCount: number,
    public posX: number,
    public posY: number,
    public width: number,
    public height: number,
  ) {
  }
}
