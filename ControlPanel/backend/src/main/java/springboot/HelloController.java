package springboot;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.http.HttpStatus;

import com.interfaces.proto.RegisterUserCommandProto.RegisterUserCommand;
import com.google.protobuf.Any;

import user.User;
import router.CommandSender;

@RestController
@ResponseBody
public class HelloController {
	@Autowired 
	private CommandSender commandSender;
	
	@PostMapping("/login")
	public ResponseEntity<String> login(@RequestBody User user) {
		
		System.out.println("Handle new login request");
		System.out.println(user.getUserId());
		System.out.println(user.getVehicleId());
		System.out.println(user.getVehicleKey());
		
		RegisterUserCommand registerUserCommand = RegisterUserCommand.newBuilder()
		.setUserId(user.getUserId())
		.setVehicleId(user.getVehicleId())
		.setVehicleKey(user.getVehicleKey())
		.build();

		Any packedCommandToSend = Any.pack(registerUserCommand);

		boolean status = commandSender.sendCommand(packedCommandToSend);

		// final boolean testingIncorrectValue = false;	
		// status = testingIncorrectValue;

		if (true == status){
			//TODO register user
			return ResponseEntity.status(HttpStatus.BAD_REQUEST).build();		
		}
		else{
			return ResponseEntity.status(HttpStatus.OK).build();		
		}
	}
}
