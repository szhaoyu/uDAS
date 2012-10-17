package nl.zybber.prototype.thrift.multiplexserver;

import nl.zybber.prototype.thrift.multiplexserver.serviceimpl.CalculatorImpl;
import nl.zybber.prototype.thrift.multiplexserver.serviceimpl.SharedImpl;
import shared.SharedService;
import tutorial.Calculator;

import com.facebook.thrift.protocol.TBinaryProtocol;
import com.facebook.thrift.protocol.TProtocolFactory;
import com.facebook.thrift.transport.TServerSocket;
import com.facebook.thrift.transport.TTransportException;
import com.facebook.thrift.transport.TTransportFactory;

public class MultiplexTestServerMain {
  public static void main(String[] args) throws TTransportException {
    TServerSocket socket = new TServerSocket(9090);
    TTransportFactory transportFactory = new TTransportFactory();
    TProtocolFactory protocolFactory = new TBinaryProtocol.Factory();
    TMultiplexServer server = new TSimpleMultiplexServer(socket, transportFactory, protocolFactory);

    server.register("shared", new SharedService.Processor(new SharedImpl()));
    server.register("calculator", new Calculator.Processor(new CalculatorImpl()));

    server.serve();
  }

  private MultiplexTestServerMain() {
  }
}
