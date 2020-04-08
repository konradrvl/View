import { HttpClientModule, HTTP_INTERCEPTORS } from '@angular/common/http';
import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';
import { MatSlideToggleModule } from '@angular/material';
import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { AngularDraggableModule } from 'angular2-draggable';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { AddBuildingComponent } from './components/add-building/add-building.component';
import { AddFloorComponent } from './components/add-floor/add-floor.component';
import { AddIotComponent } from './components/add-iot/add-iot.component';
import { AddRoomComponent } from './components/add-room/add-room.component';
import { BuildingComponent } from './components/building/building.component';
import { ChartComponent } from './components/chart/chart.component';
import { EditBuildingComponent } from './components/edit-building/edit-building.component';
import { EditFloorComponent } from './components/edit-floor/edit-floor.component';
import { EditHeatmapComponent } from './components/edit-heatmap/edit-heatmap.component';
import { EditRoomComponent } from './components/edit-room/edit-room.component';
import { HeatmapComponent } from './components/heatmap/heatmap.component';
import { HelpComponent } from './components/help/help.component';
import { HomeComponent } from './components/home/home.component';
import { LoginComponent } from './components/login/login.component';
import { NavContentComponent } from './components/nav-content/nav-content.component';
import { NavLayoutComponent } from './components/nav-layout/nav-layout.component';
import { RegisterComponent } from './components/register/register.component';
import { RoomlistComponent } from './components/roomlist/roomlist.component';
import { SettingsComponent } from './components/settings/settings.component';
import { MaterialModule } from './material.module';
import { BuildingService } from './services/Building/building.service';
import { FloorService } from './services/Floor/floor.service';
import { IotService } from './services/IoT/iot.service';
import { RoomService } from './services/Room/room.service';
import { ThemeService } from './services/Theme/theme.service';

@NgModule({
  declarations: [
    AppComponent,
    NavContentComponent,
    NavLayoutComponent,
    HomeComponent,
    SettingsComponent,
    HelpComponent,
    BuildingComponent,
    HeatmapComponent,
    LoginComponent,
    RegisterComponent,
    ChartComponent,
    RoomlistComponent,
    AddBuildingComponent,
    AddFloorComponent,
    AddRoomComponent,
    AddIotComponent,
    EditFloorComponent,
    EditBuildingComponent,
    EditRoomComponent,
    EditHeatmapComponent
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    MaterialModule,
    FormsModule,
    ReactiveFormsModule,
    AppRoutingModule,
    HttpClientModule,
    AngularDraggableModule,
    HttpModule,
    MatSlideToggleModule
  ],

  providers:
    [
      BuildingService,
      FloorService,
      RoomService,
      IotService,
      ThemeService
    ],

  bootstrap: [AppComponent]
})

export class AppModule { }
