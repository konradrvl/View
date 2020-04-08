import { Component, OnInit } from '@angular/core';
import { MatSnackBar } from '@angular/material';
import { ActivatedRoute, Router } from '@angular/router';
import { Building } from '../../models/building';
import { BuildingService } from '../../services/Building/building.service';
import { FloorService } from '../../services/Floor/floor.service';

@Component({
  selector: 'app-building',
  templateUrl: './building.component.html',
  styleUrls: ['./building.component.css']
})
export class BuildingComponent implements OnInit {

  private _building: Building;
  private _elements: Element[];

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private snackBar: MatSnackBar,
    private buildingService: BuildingService,
    private floorService: FloorService) { }

  async ngOnInit() {

    const id = +this.route.snapshot.paramMap.get('id');

    try {

      this._building = await this.buildingService.getBuilding(id);
      this._elements = (await this.floorService.getFloors(id)).map(x => new Element(x.name, `./floors/${x.id}`, x.id));

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }

  getUrl() {
    return this.router.url;
  }

  public edit() {
    this.router.navigate([`view/buildings/${this._building.id}/edit`]);
  }

  public async delete() {
    try {

      await this.buildingService.deleteBuilding(this.building.id);

      this.snackBar.open(`${this.building.name} deleted!`, 'OK', { duration: 4000 });
      this.router.navigate(['view/home']);

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }

  get elements() {
    return this._elements;
  }

  get building() {
    return this._building;
  }

}

export class Element {
  constructor(
    public name: string,
    public link: string,
    public id: number
  ) { }
}
