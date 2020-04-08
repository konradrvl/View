import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { MatSnackBar } from '@angular/material';
import { Router } from '@angular/router';
import { IotService } from '../../services/IoT/iot.service';

@Component({
  selector: 'app-add-iot',
  templateUrl: './add-iot.component.html',
  styleUrls: ['./add-iot.component.css']
})
export class AddIotComponent implements OnInit {

  private _form: FormGroup;
  private _loading = false;

  constructor(private formBuilder: FormBuilder,
    private router: Router,
    private snackBar: MatSnackBar,
    private iotService: IotService) { }

  ngOnInit() {
    this._form = this.formBuilder.group({
      id: ['', Validators.required],
    });
  }

  async onSubmit() {

    if (this.form.invalid) {
      return;
    }

    this._loading = true;

    try {

      const ioTDevice = await this.iotService.setIoTDevice(this.form.id.value);

      this.snackBar.open(`${ioTDevice.id} registered!`, 'OK', { duration: 4000 });
      this.router.navigate(['view/home']);

    } catch (e) {

      this._loading = false;
      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }

  get form() { return this._form.controls; }
  get formGroup() { return this._form; }
  get loading() { return this._loading; }

}
