import { Component, Input, OnInit } from '@angular/core';
import { Room } from '../../models/room';

@Component({
  selector: 'app-edit-heatmap',
  templateUrl: './edit-heatmap.component.html',
  styleUrls: ['./edit-heatmap.component.css'],
})
export class EditHeatmapComponent implements OnInit {

  @Input() rooms: Room[];
  private modifiedRooms: Room[] = [];
  inBounds = true;
  edge = {
    top: true,
    bottom: true,
    left: true,
    right: true
  };

  constructor() {
  }

  ngOnInit() {

  }

  resized(event, room: Room) {
    const modifiedRoom: Room = this.modifiedRooms.find(x => x.id === room.id);
    if (modifiedRoom) {
      modifiedRoom.width = Math.round(event.size.width);
      modifiedRoom.height = Math.round(event.size.height);
    } else {
      this.modifiedRooms.push(new Room(
        room.name,
        room.maxPersonCount,
        room.floorId,
        room.posX,
        room.posY,
        Math.round(event.size.width),
        Math.round(event.size.height),
        room.id,
        room.iotDeviceId
      ));
    }
  }

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

  getRooms(): Room[] {
    return this.modifiedRooms;
  }

}
