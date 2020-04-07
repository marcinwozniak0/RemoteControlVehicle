import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs/Observable';
import { User } from 'model/user';
 

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})

@Injectable()
export class LoginComponent implements OnInit {
  form: FormGroup;
  public loginInvalid: boolean;
  public user: User
  private formSubmitAttempt: boolean;
  private usersUrl: string;

  constructor(
    private http: HttpClient,
    private fb: FormBuilder,
    private route: ActivatedRoute,
    private router: Router,
  ) {
    this.usersUrl = 'http://localhost:8080/login';
    this.user = new User();
  }

  async ngOnInit() {
    this.form = this.fb.group({
      username: ['', Validators.required],
      vehicleId: ['', Validators.required],
      vehicleKey: ['', Validators.required]
    });

  }

  async onSubmit() {
    this.loginInvalid = false;
    this.formSubmitAttempt = false;
    if (this.form.valid) {
      try {
        this.user.username = this.form.get('username').value;
        this.user.vehicleId = this.form.get('vehicleId').value;
        this.user.vehicleKey = this.form.get('vehicleKey').value;
        console.log("before sending");
        this.http.post<any[]>(this.usersUrl, this.user, {observe: 'response'}).subscribe(response =>{
          console.log("inside sending");
          console.log(response.status);
        });
        
        console.log("after sending");
        
      } catch (err) {
        this.loginInvalid = true;
      }
    } 
    else {
      print();
      this.formSubmitAttempt = true;
    }
  }
}