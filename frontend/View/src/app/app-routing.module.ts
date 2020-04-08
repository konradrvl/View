import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AddBuildingComponent } from './components/add-building/add-building.component';
import { AddFloorComponent } from './components/add-floor/add-floor.component';
import { AddIotComponent } from './components/add-iot/add-iot.component';
import { AddRoomComponent } from './components/add-room/add-room.component';
import { BuildingComponent } from './components/building/building.component';
import { ChartComponent } from './components/chart/chart.component';
import { EditBuildingComponent } from './components/edit-building/edit-building.component';
import { EditFloorComponent } from './components/edit-floor/edit-floor.component';
import { EditRoomComponent } from './components/edit-room/edit-room.component';
import { HeatmapComponent } from './components/heatmap/heatmap.component';
import { HelpComponent } from './components/help/help.component';
import { HomeComponent } from './components/home/home.component';
import { LoginComponent } from './components/login/login.component';
import { NavLayoutComponent } from './components/nav-layout/nav-layout.component';
import { RegisterComponent } from './components/register/register.component';
import { SettingsComponent } from './components/settings/settings.component';
import { AuthGuard } from './guards/auth.guard';



const routes: Routes = [
  { path: '', redirectTo: '/login', pathMatch: 'full' },
  { path: 'login', component: LoginComponent },
  { path: 'register', component: RegisterComponent },
  {
    path: 'view', component: NavLayoutComponent, canActivate: [AuthGuard], children: [
      { path: '', redirectTo: '/home', pathMatch: 'full' },
      { path: 'home', canActivate: [AuthGuard], component: HomeComponent },
      { path: 'settings', canActivate: [AuthGuard], component: SettingsComponent },
      { path: 'help', canActivate: [AuthGuard], component: HelpComponent },
      { path: 'building/add', canActivate: [AuthGuard], component: AddBuildingComponent },
      { path: 'buildings/:id', canActivate: [AuthGuard], component: BuildingComponent },
      { path: 'buildings/:id/add', canActivate: [AuthGuard], component: AddFloorComponent },
      { path: 'buildings/:id/edit', canActivate: [AuthGuard], component: EditBuildingComponent },
      { path: 'floors/:id', canActivate: [AuthGuard], component: HeatmapComponent },
      { path: 'floors/:id/add', canActivate: [AuthGuard], component: AddRoomComponent },
      { path: 'floors/:id/edit', canActivate: [AuthGuard], component: EditFloorComponent },
      { path: 'rooms/:id', canActivate: [AuthGuard], component: ChartComponent },
      { path: 'rooms/:id/chart', canActivate: [AuthGuard], component: ChartComponent },
      { path: 'rooms/:id/edit', canActivate: [AuthGuard], component: EditRoomComponent },
      { path: 'ioTDevices/add', canActivate: [AuthGuard], component: AddIotComponent }
    ]
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
