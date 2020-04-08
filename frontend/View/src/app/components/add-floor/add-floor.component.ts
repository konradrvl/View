import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { MatSnackBar } from '@angular/material';
import { ActivatedRoute, Router } from '@angular/router';
import { Floor } from '../../models/floor';
import { FloorService } from '../../services/Floor/floor.service';

@Component({
  selector: 'app-add-floor',
  templateUrl: './add-floor.component.html',
  styleUrls: ['./add-floor.component.css']
})
export class AddFloorComponent implements OnInit {

  private _form: FormGroup;
  private _loading = false;

  constructor(private formBuilder: FormBuilder,
    private router: Router,
    private route: ActivatedRoute,
    private snackBar: MatSnackBar,
    private floorService: FloorService) { }

  ngOnInit() {
    this._form = this.formBuilder.group({
      name: ['', Validators.required],
    });
  }

  async onSubmit() {

    if (this.form.invalid) {
      return;
    }

    this._loading = true;

    try {

      const buildingId = +this.route.snapshot.paramMap.get('id');
      const newFloor = new Floor(this.form.name.value, buildingId);
      const floor = await this.floorService.createFloor(newFloor);

      this.snackBar.open(`${floor.name} created!`, 'OK', { duration: 4000 });
      this.router.navigate([`view/floors/${floor.id}`]);

    } catch (e) {

      this._loading = false;
      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }

  get form() { return this._form.controls; }
  get formGroup() { return this._form; }
  get loading() { return this._loading; }

}
