import { Component, OnInit } from '@angular/core';
import { MatSnackBar } from '@angular/material';
import { ActivatedRoute, Router, NavigationEnd } from '@angular/router';
import { Chart } from 'chart.js';
import { Occupation } from '../../models/occupation';
import { Room } from '../../models/room';
import { RoomService } from '../../services/Room/room.service';

@Component({
  selector: 'app-chart',
  templateUrl: './chart.component.html',
  styleUrls: ['./chart.component.css']
})

export class ChartComponent implements OnInit {

  chart: Chart;
  _room: Room;
  private _occupations: Occupation[];
  private _dates;
  private _personCount;

  constructor(private route: ActivatedRoute,
    private router: Router,
    private snackBar: MatSnackBar,
    private _roomService: RoomService) { }

  async ngOnInit() {
    this.router.routeReuseStrategy.shouldReuseRoute = () => false;
    try {

      this._room = await this._roomService.getRoom(+this.route.snapshot.paramMap.get('id'));

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }

    await this.getOccupations();
    await this.seperateOccupancy();
    await this.drawBarChart();
  }



  private async getOccupations() {
    const from = new Date();
    from.setHours(from.getDay() - 1);

    try {

      this._occupations = await this._roomService.getRoomHistory(this._room.id, from, new Date);

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }



  private drawBarChart() {
    const colours = this._personCount.map(value => value < 0 ? 'grey' : 'rgba(48, 63, 159, 0.4)');

    const clearedData = this._personCount.map(value => value < 0 ? 1 : value);

    this.chart = new Chart('chart', {
      type: 'bar',
      data: {
        labels: this._dates,
        datasets: [
          {
            data: clearedData,
            borderColor: colours,
            backgroundColor: colours,
            pointBackgroundColor: 'rgba(48, 63, 159, 1)',
            pointHoverBackgroundColor: 'rgba(48, 63, 159, 1)',
            pointHoverBorderColor: 'rgba(48, 63, 159, 0.6)',
            pointHoverBorderWidth: 6,
            borderWidth: 3,
          }
        ]
      },
      options: {
        legend: {
          display: false
        },
        scales: {
          xAxes: [{
            display: true,
          },
          ],
          yAxes: [{
            display: true,
          }],
        }
      }
    });
  }


  private seperateOccupancy() {
    this._dates = [];
    this._personCount = [];

    for (const occupation of this._occupations) {
      const options = { year: 'numeric', month: 'numeric', day: 'numeric' };

      this._personCount.push(occupation.personCount);
      const jsdate = new Date(occupation.time);
      this._dates.push(jsdate.toLocaleDateString('en-EN', options) + ' ' + jsdate.toLocaleTimeString('en-EN'));
    }
  }

  public edit() {
    this.router.navigate([`view/rooms/${this._room.id}/edit`]);
  }

  public async delete() {
    try {

      await this._roomService.deleteRoom(this._room.id);

      this.snackBar.open(`${this._room.name} deleted!`, 'OK', { duration: 4000 });
      this.router.navigate([`view/floors/${this._room.floorId}`]);

    } catch (e) {

      this.snackBar.open(`Error: ${e.message}`, 'OK', { duration: 4000 });

    }
  }
}
