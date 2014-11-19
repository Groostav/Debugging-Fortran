package com.empowerops;

import com.sun.jna.*;

import java.nio.file.Path;
import java.nio.file.Paths;

import static java.lang.System.out;

public class Main {

    public static final Path PathToDll = Paths.get(".").toAbsolutePath().getParent().getParent().resolve("Debug").resolve("api.dll").toAbsolutePath();
//    public static final Path PathToDll = Paths.get(".").toAbsolutePath().getParent().getParent().resolve("api").resolve("Release").resolve("api.dll").toAbsolutePath();

    public static class Pointer<TPointedAt extends Number> extends PointerType {

        public Pointer() {}

        public Pointer(com.sun.jna.Pointer p) {
            super(p);
        }

        public int[]    asIntArray(int arraySize) { return getPointer().getIntArray(0, arraySize);}
        public double[] asDoubleArray(int arraySize){ return getPointer().getDoubleArray(0, arraySize); }
        public char[] asCharArray(int arraySize){ return getPointer().getCharArray(0, arraySize); }
    }

    @FunctionalInterface
    public static interface NumEvaluator extends Callback {
        public double run(int length, double aDouble);
    }

    @FunctionalInterface
    public static interface ArrayEvaluator extends Callback{
        public double run(int length, double ADouble, Pointer<Double> doubleArray);
    }

    public interface api extends Library{
        void pauseOptimization(boolean meh);
        void acceptCallback(NumEvaluator evaluator);
        void acceptArrayCallback(ArrayEvaluator evaluator,SomeStruct someStruct);
    }


    public static void main(String[] args) {

        api api = resolveAPI();

        out.println("java: os.arch is " + System.getProperty("os.arch"));
        
        SomeStruct someStruct = new SomeStruct();
        someStruct.someInt = 5;
        someStruct.someDouble = 25.48;

        out.println("java: calling fortran now: FORTRAN{");
        api.acceptArrayCallback(Main::doCallback, someStruct);
        out.println("java: call to fortran to accept callback finished.");
    }

    public static double doCallback(int length, double aDouble, Pointer<Double> doubleArray){
        out.println("java: hello again from java, things seem to be working OK over here on " + System.getProperty("os.arch"));
        out.println("java: got length:" + length);
        out.println("java: got aDouble:" + aDouble);
        out.println("java: got doubleArray: " + doubleArray + " { " + doubleArray.asDoubleArray(2)[0] + ", " + doubleArray.asDoubleArray(2)[1] + "...}");
        return 42;
    }

    private static api resolveAPI() {

        String fullyQualifiedPath = PathToDll.toUri().getPath();

        String parentFolder = fullyQualifiedPath.substring(0, fullyQualifiedPath.lastIndexOf("/"));
        String fileName = fullyQualifiedPath.substring(fullyQualifiedPath.lastIndexOf("/") +1, fullyQualifiedPath.length()).split("\\.")[0];

        NativeLibrary.addSearchPath(fileName, parentFolder);

        return (api) Native.loadLibrary(fileName, api.class);
    }
}
