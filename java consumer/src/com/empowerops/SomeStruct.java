package com.empowerops;

import com.sun.jna.Structure;

import java.util.Arrays;
import java.util.List;

/**
 * Created by George on 2014-11-19.
 */
public class SomeStruct extends Structure{

    public int someInt;
    public double someDouble;

    @Override
    public List getFieldOrder(){
        return Arrays.asList("someInt", "someDouble");
    }
}
