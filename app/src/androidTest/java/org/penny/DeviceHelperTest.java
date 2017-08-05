package org.penny;

import android.os.Build;
import android.support.test.runner.AndroidJUnit4;
import android.util.Log;

import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;

/**
 * Created by lucky on 05/08/2017.
 */

@RunWith(AndroidJUnit4.class)
public class DeviceHelperTest {
    private static final String TAG = DeviceHelperTest.class.getSimpleName();

    @Test
    public void testNativeGetBootTime() {
        Log.d(TAG, "testNativeGetBootTime...");
        Log.d(TAG, "boot time: " + DeviceHelper.native_getBootTime());
    }

    @Test
    public void testGetBootTime() {
        Log.d(TAG, "testGetBootTime...");
        Log.d(TAG, "boot time: " + DeviceHelper.getBootTime());

        if (Build.VERSION.SDK_INT >= 17) {
            assertEquals(DeviceHelper.native_getBootTime(), DeviceHelper.getBootTime() / 1000);
        }
    }
}
