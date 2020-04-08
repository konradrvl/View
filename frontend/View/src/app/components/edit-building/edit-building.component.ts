import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { MatSnackBar } from '@angular/material';
import { ActivatedRoute, Router } from '@angular/router';
import { Building } from '../../models/building';
import { BuildingService } from '../../services/Building/building.service';

@Component({
  selector: 'app-edit-building',
  templateUrl: './edit-building.component.html',
  styleUrls: ['./edit-building.component.css']
})
export class EditBuildingComponent implements OnInit {

  private _building: Building;
  private _form: FormGroup;
  private _loading = false;

  constructor(private formBuilder: FormBuilder,
    private router: Router,
    private route: ActivatedRoute,
    private snackBar: MatSnackBar,
    private buildingService: BuildingService,
  ) { }

  ngOnInit() {
    this._form = this.formBuilder.group({
      name: ['', Validators.required],
    });
    this.getBuilding();
  }

  async getBuilding() {

    this._loading = true;

    const buildingId = +this.route.snapshot.paramMap.get('id');

    try {

      this._building = await this.buildingService.getBuilding(buildingId);
      this.form.name.setValue(this.building.name);

      this._loading = false;

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });
      this.router.navigate([`view/buildings/${buildingId}`]);

    }
  }

  async onSubmit() {

    if (this.form.invalid) {
      return;
    }

    this._loading = true;

    try {

      this.building.name = this.form.name.value;
      const building = await this.buildingService.editBuilding(this.building.id, this.building);

      this.snackBar.open(`${building.name} edited!`, 'OK', { duration: 4000 });
      this.router.navigate([`view/buildings/${building.id}`]);

    } catch (e) {

      this._loading = false;
      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }

  get form() { return this._form.controls; }
  get formGroup() { return this._form; }
  get loading() { return this._loading; }
  get building() { return this._building }

}
