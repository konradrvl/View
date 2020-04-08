import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { MatSnackBar } from '@angular/material';
import { ActivatedRoute, Router } from '@angular/router';
import { Room } from '../../models/room';
import { IotService } from '../../services/IoT/iot.service';
import { RoomService } from '../../services/Room/room.service';

@Component({
  selector: 'app-edit-room',
  templateUrl: './edit-room.component.html',
  styleUrls: ['./edit-room.component.css']
})
export class EditRoomComponent implements OnInit {

  private _room: Room;
  private _form: FormGroup;
  private _loading = false;
  private _iotDevices: string[] = [];

  constructor(private formBuilder: FormBuilder,
    private router: Router,
    private route: ActivatedRoute,
    private snackBar: MatSnackBar,
    private roomService: RoomService,
    private iotService: IotService,
  ) { }

  ngOnInit() {

    this._form = this.formBuilder.group({
      name: ['', Validators.required],
      maxPersonCount: ['', [Validators.required, Validators.pattern('\\d*')]],
      posX: ['', [Validators.required, Validators.pattern('\\d*')]],
      posY: ['', [Validators.required, Validators.pattern('\\d*')]],
      width: ['', [Validators.required, Validators.pattern('\\d*')]],
      height: ['', [Validators.required, Validators.pattern('\\d*')]],
      iotDeviceId: ['']
    });

    this.getRoom()
  }

  async getRoom() {

    this._loading = true;

    const roomId = +this.route.snapshot.paramMap.get('id');

    try {

      this._room = await this.roomService.getRoom(roomId);

      this.form.name.setValue(this.room.name);
      this.form.maxPersonCount.setValue(this.room.maxPersonCount);
      this.form.posX.setValue(this.room.posX);
      this.form.posY.setValue(this.room.posY);
      this.form.width.setValue(this.room.width);
      this.form.height.setValue(this.room.height);
      this.form.iotDeviceId.setValue(this.room.iotDeviceId);

      this._iotDevices = await this.iotService.getIoTDevices();

      this._loading = false;

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });
      this.router.navigate([`view/buildings/${roomId}`]);

    }
  }

  async onSubmit() {

    if (this.form.invalid) {
      return;
    }

    this._loading = true;

    try {

      this.room.name = this.form.name.value;
      this.room.maxPersonCount = +this.form.maxPersonCount.value;
      this.room.posX = +this.form.posX.value;
      this.room.posY = +this.form.posY.value;
      this.room.width = +this.form.width.value;
      this.room.height = +this.form.height.value;
      this.room.iotDeviceId = this.form.iotDeviceId.value === '' ? undefined : this.form.iotDeviceId.value

      const room = await this.roomService.editRoom(this.room.id, this.room);

      this.snackBar.open(`${room.name} edited!`, 'OK', { duration: 4000 });
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
  get room() { return this._room }

}
