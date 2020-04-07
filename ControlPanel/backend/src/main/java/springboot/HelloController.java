package springboot;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.http.ResponseEntity;
import org.springframework.http.HttpStatus;

import user.User;

@RestController
@ResponseBody
public class HelloController {

	@PostMapping("/login")
	public ResponseEntity<String> login(@RequestBody User user) {
		
		System.out.println("Handle new login request");
		System.out.println(user.getUsername());
		System.out.println(user.getVehicleId());
		System.out.println(user.getVehicleKey());
		
		//TODO
		//1. Send request to CU
		//2. Register or reject user

		final int testingIncorrectValue = 1;	

		if (testingIncorrectValue == user.getVehicleId()){
			return ResponseEntity.status(HttpStatus.BAD_REQUEST).build();				
		} 
		else{
			return ResponseEntity.status(HttpStatus.OK).build();
		}
	}
}
