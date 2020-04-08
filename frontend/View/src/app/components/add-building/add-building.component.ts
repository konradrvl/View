import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { MatSnackBar } from '@angular/material';
import { Router } from '@angular/router';
import { Building } from '../../models/building';
import { BuildingService } from '../../services/Building/building.service';

@Component({
  selector: 'app-add-building',
  templateUrl: './add-building.component.html',
  styleUrls: ['./add-building.component.css']
})
export class AddBuildingComponent implements OnInit {

  private _form: FormGroup;
  private _loading = false;

  constructor(private formBuilder: FormBuilder,
    private router: Router,
    private snackBar: MatSnackBar,
    private buildingService: BuildingService) { }

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

      const newBuilding = new Building(this.form.name.value);
      const building = await this.buildingService.createBuilding(newBuilding);

      this.snackBar.open(`${building.name} created!`, 'OK', { duration: 4000 });
      this.router.navigate([`view/buildings/${building.id}`]);

    } catch (e) {

      this._loading = false;
      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }

  get form() { return this._form.controls; }
  get formGroup() { return this._form; }
  get loading() { return this._loading; }

}
