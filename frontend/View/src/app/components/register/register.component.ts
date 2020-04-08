import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { MatSnackBar } from '@angular/material';
import { Router } from '@angular/router';
import { AuthenticationService } from '../../services/Authentication/authentication.service';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent implements OnInit {

  private _form: FormGroup;
  private _loading = false;

  constructor(private formBuilder: FormBuilder,
    private router: Router,
    private snackBar: MatSnackBar,
    private authenticationService: AuthenticationService) { }

  ngOnInit() {
    this._form = this.formBuilder.group({
      username: ['', Validators.required],
      password: ['', Validators.required]
    });
  }

  async onSubmit() {

    if (this.form.invalid) {
      return;
    }

    this._loading = true;

    try {

      await this.authenticationService.register(this.form.username.value, this.form.password.value);

      this.snackBar.open(`Registered as ${this.form.username.value}!`, 'OK', { duration: 4000 });
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
