package router;

import com.interfaces.proto.InitCommandsProto.*;
import com.interfaces.proto.RouterGrpc;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;

public class CommandSender {
    public CommandSender() {
    ManagedChannel channel = ManagedChannelBuilder.forAddress("localhost", 5000)
    .usePlaintext()
    .build();
    
    RouterGrpc.RouterBlockingStub stub 
        = RouterGrpc.newBlockingStub(channel);

    HelloReply helloReply = stub.sayHello(HelloRequest.newBuilder()
        .setName("JAVA command sender")
        .build());

    }
}