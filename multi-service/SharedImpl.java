package nl.zybber.prototype.thrift.multiplexserver.serviceimpl;

import com.facebook.thrift.TException;

import shared.SharedStruct;
import shared.SharedService.Iface;

public class SharedImpl implements Iface {
  public SharedImpl() {
    super();
  }

  @Override
  public SharedStruct getStruct(int key) throws TException {
    SharedStruct result = new SharedStruct();
    result.setKey(key);
    result.setValue("Always the same (Shared).");
    return result;
  }

}
