package at.roomControlSystem;

import android.content.Context;

public class ContextHolder {
	private static ContextHolder instance = new ContextHolder();
	public static ContextHolder getInstance()
	{
		return instance;
	}
	private ContextHolder(){}
	public Context getContext() {
		return cnt;
	}
	public void setContext(Context cnt) {
		this.cnt = cnt;
	}
	private Context cnt;

}
