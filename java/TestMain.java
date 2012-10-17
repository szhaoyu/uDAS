
import java.net.URLClassLoader;
import java.net.URL;

public class TestMain {
	public static void main(String[] args) {
		URL jarFile = new URL("test.jar");
		URLClassLoader myClassLoader = new  URLClassLoader( new URL[] { url } ); 
		Class myClass = myClassLoader.loadClass("TestOne"); 
		TestInterface test1 = myClass.newInstance();
		test1.hello( " interface " );
		TestAbstract  test2 =  myClass.newInstance();
		test2.helloAbs( " here " );
	}
}
