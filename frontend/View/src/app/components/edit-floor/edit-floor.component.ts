import { Component, OnInit, ViewChild } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { MatSnackBar } from '@angular/material';
import { ActivatedRoute, Router } from '@angular/router';
import { Floor } from '../../models/floor';
import { Room } from '../../models/room';
import { FloorService } from '../../services/Floor/floor.service';
import { RoomService } from '../../services/Room/room.service';
import { EditHeatmapComponent } from '../edit-heatmap/edit-heatmap.component';

@Component({
  selector: 'app-edit-floor',
  templateUrl: './edit-floor.component.html',
  styleUrls: ['./edit-floor.component.css']
})
export class EditFloorComponent implements OnInit {

  @ViewChild(EditHeatmapComponent) child: EditHeatmapComponent;
  private _floor: Floor;
  private _form: FormGroup;
  private _loading = false;
  private _rooms: Room[];

  constructor(private formBuilder: FormBuilder,
    private router: Router,
    private route: ActivatedRoute,
    private snackBar: MatSnackBar,
    private floorService: FloorService,
    private roomService: RoomService
  ) { }

  async ngOnInit() {
    this._form = this.formBuilder.group({
      name: ['', Validators.required],
    });
    this.getFloor();

    const floorId = +this.route.snapshot.paramMap.get('id');
    this._rooms = await this.roomService.getRooms(floorId);
  }

  async getFloor() {

    this._loading = true;

    const floorId = +this.route.snapshot.paramMap.get('id');

    try {

      this._floor = await this.floorService.getFloor(floorId);

      this.form.name.setValue(this.floor.name);

      this._loading = false;

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });
      this.router.navigate([`view/buildings/${floorId}`]);

    }
  }

  async onSubmit() {


    if (this.form.invalid) {
      return;
    }

    this._loading = true;

    try {

      const alteredRooms = this.child.getRooms();

      for (const room of alteredRooms) {
        await this.roomService.editRoom(room.id, room);
      }

      this.floor.name = this.form.name.value;
      const floor = await this.floorService.editFloor(this.floor.id, this.floor);

      this.snackBar.open(`${floor.name} edited!`, 'OK', { duration: 4000 });
      this.router.navigate([`view/floors/${floor.id}`]);

    } catch (e) {

      this._loading = false;
      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }

  }


  private async updateRoom(roomId: number, posX: number, posY: number, width: number, height: number) {
    try {

      const newRoom = await this.roomService.getRoom(roomId);

      newRoom.posX = posX;
      newRoom.posY = posY;
      newRoom.width = width;
      newRoom.height = height;

      this.roomService.editRoom(newRoom.id, newRoom);

    } catch (e) {
      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });
    }

  }

  get form() { return this._form.controls; }
  get formGroup() { return this._form; }
  get loading() { return this._loading; }
  get floor() { return this._floor }
  get rooms(): Room[] { return this._rooms }

}
