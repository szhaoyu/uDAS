
public class TestOne extends TestAbstract implements TestInterface {
	public void hello( String one ) {
		(new TestTwo()).hello( one );
	}
	public void helloAbs( String one ) {
		TestTwo.helloAbs( one );
	}
}
