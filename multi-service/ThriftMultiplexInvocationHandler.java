package nl.zybber.prototype.thrift.multiplexserver;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

import shared.SharedStruct;

import com.facebook.thrift.protocol.TMessage;
import com.facebook.thrift.protocol.TMessageType;
import com.facebook.thrift.protocol.TProtocol;

public class ThriftMultiplexInvocationHandler implements InvocationHandler {
  private String serviceName_;
  private TProtocol oprot_;
  private Set<Class<?>> interfaces_ = new HashSet<Class<?>>();
  private Object target_;

  public <TInterface> ThriftMultiplexInvocationHandler(String serviceName,
          TProtocol oprot,
          Class<TInterface> iface,
          TInterface target) {
    serviceName_ = serviceName;
    oprot_ = oprot;
    addInterface(iface);
    target_ = target;
  }

  @Override
  public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
    Object result;
    if (interfaces_.contains(method.getDeclaringClass())) {
      oprot_.writeMessageBegin(new TMessage(serviceName_, TMessageType.SERVICE_SELECTION, 0));
      try {
        result = method.invoke(target_, args);
      } catch (InvocationTargetException e) {
        throw e.getCause();
      }
      oprot_.writeMessageEnd();
      oprot_.getTransport().flush();
    } else {
      try {
        result = method.invoke(target_, args);
      } catch (InvocationTargetException e) {
        throw e;
      }
    }
    return result;
  }

  private void addInterface(Class<?> iface) {
    interfaces_.add(iface);
    for (Class<?> superiface : iface.getInterfaces()) {
      addInterface(superiface);
    }
  }
}
