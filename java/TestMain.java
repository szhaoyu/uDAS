
import java.net.URLClassLoader;
import java.net.URL;

public class TestMain {
	public static void main(String[] args) {
		try {
			//File jar = new File("d:\\test\\commons-lang-2.2.jar");  
			//URL[] urls = new URL[]{jar.toURI().toURL()};  
			//jar:http://hostname/my.jar!/"
			//jar:file:/c:/my.jar!/
			URL jarFile = new URL("jar:file:/F:/UDAS/java/test.jar!/");
			URLClassLoader myClassLoader = new  URLClassLoader( new URL[] { jarFile } ); 
			Class myClass = myClassLoader.loadClass("TestOne"); 
			TestInterface test1 = (TestInterface)myClass.newInstance();
			test1.hello( " interface " );
			TestAbstract  test2 = (TestAbstract) myClass.newInstance();
			test2.helloAbs( " here " );
			myClass = null;
			System.gc();
		}
		catch( Exception e ) {
			System.out.println( e );
		}
	}
}

