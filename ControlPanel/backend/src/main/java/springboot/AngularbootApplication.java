package springboot;

import java.util.Arrays;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.Bean;

import router.CommandReceiver;
import io.grpc.Server;
import io.grpc.ServerBuilder;
import java.io.IOException;

@SpringBootApplication
public class AngularbootApplication {

	public static void main(String[] args) throws IOException, InterruptedException {
		
		Server server = ServerBuilder
          .forPort(3000)
		  .addService(new CommandReceiver()).build();
		  
		server.start();
		
		SpringApplication.run(AngularbootApplication.class, args);

		server.awaitTermination();
	}

	@Bean
	public CommandLineRunner commandLineRunner(ApplicationContext ctx) {
		return args -> {

			System.out.println("Let's inspect the beans provided by Spring Boot:");

			String[] beanNames = ctx.getBeanDefinitionNames();
			Arrays.sort(beanNames);
			for (String beanName : beanNames) {
				System.out.println(beanName);
			}

		};
	}

}

