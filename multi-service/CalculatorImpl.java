package nl.zybber.prototype.thrift.multiplexserver.serviceimpl;

import com.facebook.thrift.TException;

import shared.SharedStruct;
import tutorial.InvalidOperation;
import tutorial.Operation;
import tutorial.Work;
import tutorial.Calculator.Iface;

public class CalculatorImpl extends SharedImpl implements Iface {
  public CalculatorImpl() {
  }

  @Override
  public SharedStruct getStruct(int key) throws TException {
    SharedStruct result = new SharedStruct();
    result.setKey(key);
    result.setValue("Always the same (Calculator).");
    return result;
  }

  @Override
  public int add(int num1, int num2) throws TException {
    return num1 + num2;
  }

  @Override
  public int calculate(int logid, Work work) throws InvalidOperation, TException {
    int result;
    switch (work.getOp()) {
    case Operation.ADD:
      result = work.getNum1() + work.getNum2();
      break;
    case Operation.SUBTRACT:
      result = work.getNum1() - work.getNum2();
      break;
    case Operation.MULTIPLY:
      result = work.getNum1() * work.getNum2();
      break;
    case Operation.DIVIDE:
      result = work.getNum1() / work.getNum2();
      break;
    default:
      throw new IllegalArgumentException("Unknown operation: " + work.getOp());
    }
    return result;
  }

  @Override
  public void ping() throws TException {
    System.out.println("Server pinged.");
  }

  @Override
  public void zip() throws TException {
    System.out.println("Server zipped.");
  }
}
