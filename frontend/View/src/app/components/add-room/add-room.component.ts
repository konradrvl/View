import { Component, OnInit, ViewChild } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { MatSnackBar } from '@angular/material';
import { ActivatedRoute, Router } from '@angular/router';
import { Room } from '../../models/room';
import { IotService } from '../../services/IoT/iot.service';
import { RoomService } from '../../services/Room/room.service';
import { EditHeatmapComponent } from '../edit-heatmap/edit-heatmap.component';

@Component({
  selector: 'app-add-room',
  templateUrl: './add-room.component.html',
  styleUrls: ['./add-room.component.css'],
})
export class AddRoomComponent implements OnInit {

  @ViewChild(EditHeatmapComponent) child: EditHeatmapComponent;
  private _form: FormGroup;
  private _loading = false;
  private _iotDevices: string[] = [];
  private _rooms: Room[];

  constructor(private formBuilder: FormBuilder,
    private router: Router,
    private route: ActivatedRoute,
    private snackBar: MatSnackBar,
    private roomService: RoomService,
    private iotService: IotService
  ) { }

  async ngOnInit() {

    this.getDevices();

    this._form = this.formBuilder.group({
      name: ['', Validators.required],
      maxPersonCount: ['', [Validators.required, Validators.pattern('\\d*')]],
      iotDeviceId: ['']
    });

    const floorId = +this.route.snapshot.paramMap.get('id');
    this._rooms = await this.roomService.getRooms(floorId);
    this._rooms.push(new Room(
      'new Room',
      undefined,
      floorId,
      0,
      0,
      50,
      50,
      0,
      undefined,
    ));
  }


  async getDevices() {
    this._iotDevices = await this.iotService.getIoTDevices();
  }

  async onSubmit() {


    if (this.form.invalid) {
      return;
    }

    this._loading = true;

    try {

      const newRoom = this.child.getRooms().find(x => x.id === 0);
      newRoom.name = this.form.name.value;
      newRoom.maxPersonCount = this.form.maxPersonCount.value;
      newRoom.iotDeviceId = this.form.iotDeviceId.value === '' ? undefined : this.form.iotDeviceId.value;

      const room = await this.roomService.createRoom(newRoom);

      const alteredRooms = this.child.getRooms().filter(x => x.id !== 0);
      for (const alteredRoom of alteredRooms) {
        await this.roomService.editRoom(alteredRoom.id, alteredRoom);
      }

      this.snackBar.open(`${room.name} created!`, 'OK', { duration: 4000 });

      this.router.navigate([`view/rooms/${room.id}`]);

    } catch (e) {

      this._loading = false;
      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }

  get form() { return this._form.controls; }
  get formGroup() { return this._form; }
  get loading() { return this._loading; }
  get ioTDevices() { return this._iotDevices }
  get rooms(): Room[] { return this._rooms }

}
