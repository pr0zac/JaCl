class JaCl {
  private native void print();
  public static void main(String[] args) {
     new JaCl().print();
  }
  static {
     System.loadLibrary("JaCl"); }
}
