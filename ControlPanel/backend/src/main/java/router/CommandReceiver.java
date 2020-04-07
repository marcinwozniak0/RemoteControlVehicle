package router;

import io.grpc.stub.StreamObserver;

import com.interfaces.proto.RouterGrpc;
import com.interfaces.proto.InitCommandsProto.*;

public class CommandReceiver extends RouterGrpc.RouterImplBase {
 
    @Override
    public void sayHello(HelloRequest request, StreamObserver<HelloReply> responseObserver) {
 
        String greeting = new StringBuilder()
          .append("Hello, from java app")
          .toString();
 
          HelloReply response = HelloReply.newBuilder()
          .setMessage(greeting)
          .build();
 
        responseObserver.onNext(response);
        responseObserver.onCompleted();
    }
}