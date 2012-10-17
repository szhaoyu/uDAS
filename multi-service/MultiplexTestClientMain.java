package nl.zybber.prototype.thrift.multiplexserver;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Proxy;
import java.lang.reflect.UndeclaredThrowableException;
import java.util.Collection;
import java.util.HashSet;

import shared.SharedService;
import shared.SharedStruct;
import tutorial.Calculator;

import com.facebook.thrift.TApplicationException;
import com.facebook.thrift.TException;
import com.facebook.thrift.protocol.TBinaryProtocol;
import com.facebook.thrift.transport.TSocket;

public class MultiplexTestClientMain {
  private static SharedService.Iface shared;
  private static Calculator.Iface calculator;
  private static Calculator.Iface calculatorByAnotherName;

  public static void main(String[] args) throws TException {
    TSocket socket = new TSocket("localhost", 9090);
    socket.open();
    TBinaryProtocol protocol = new TBinaryProtocol(socket);

    shared = (SharedService.Iface) createProxy("shared", SharedService.Iface.class, protocol, new SharedService.Client(
            protocol));
    calculator = (Calculator.Iface) createProxy("calculator", Calculator.Iface.class, protocol, new Calculator.Client(
            protocol));
    calculatorByAnotherName = (Calculator.Iface) createProxy("calculator2", Calculator.Iface.class, protocol,
            new Calculator.Client(protocol));

    callSharedGetStruct();
    callCalculatorAdd();
    callCalculatorPing();
    callCalculatorGetStruct();
    callCalculatorZip();
    callSharedGetStruct();
    try {
      callCalculatorByAnotherNameAdd();
    } catch (TApplicationException e) {
      System.out.println("ERROR: " + e.getMessage());
    }
    callCalculatorGetStruct();
    callCalculatorZip();
  }

  private static <TInterface> TInterface createProxy(String serviceName, Class<TInterface> iface,
          TBinaryProtocol protocol, TInterface target) {
    return (TInterface) Proxy.newProxyInstance(iface.getClassLoader(), new Class[] { iface, },
            new ThriftMultiplexInvocationHandler(serviceName, protocol, iface, target));
  }

  private static void callSharedGetStruct() throws TException {
    SharedStruct sharedStruct = shared.getStruct(1);
    System.out.println("Shared.getStruct(int): key: " + sharedStruct.getKey() + ", value: " + sharedStruct.getValue());
  }

  private static void callCalculatorGetStruct() throws TException {
    SharedStruct sharedStruct = calculator.getStruct(2);
    System.out.println("Calculator.getStruct(int): key: " + sharedStruct.getKey() + ", value: "
            + sharedStruct.getValue());
  }

  private static void callCalculatorAdd() throws TException {
    int result = calculator.add(1, 1);
    System.out.println("Calculator.add(int, int): result: " + result);
  }

  private static void callCalculatorZip() throws TException {
    calculator.zip();
    System.out.println("Calculator.zip()");
  }

  private static void callCalculatorPing() throws TException {
    calculator.ping();
    System.out.println("Calculator.ping()");
  }

  private static void callCalculatorByAnotherNameAdd() throws TException {
    int result = calculatorByAnotherName.add(1, 1);
    System.out.println("Calculator by another name.add(int, int): result: " + result);
  }

  private MultiplexTestClientMain() {
  }
}
