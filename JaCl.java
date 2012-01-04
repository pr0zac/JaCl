class JaCl {
  static {
     System.loadLibrary("JaCl");
  }

  protected long ptr;

  public JaCl() {
    this.ptr = initCppSide();
  }

  public String nonce() {
    return nonce(this.ptr);
  }
  public void setRemoteNonce(String rn) {
    setRemoteNonce(this.ptr, rn);
  }
  public void genNewNonce() {
    genNewNonce(this.ptr);
  }

  public String publicKey() {
    return publicKey(this.ptr);
  }
  public String secretKey() {
    return secretKey(this.ptr);
  }
  public void setRemoteKey(String rk) {
    setRemoteKey(this.ptr, rk);
  }
  public void genNewKeys() {
    genNewKeys(this.ptr);
  }

  public String secret() {
    return secret(this.ptr);
  }
  public void setSecret(String ns) {
    setSecret(this.ptr, ns);
  }
  public void genNewSecret() {
    genNewSecret(this.ptr);
  }

  public String publicDecrypt(String enc_msg) {
    return publicDecrypt(this.ptr, enc_msg);
  }
  public String publicEncrypt(String msg) {
    return publicEncrypt(this.ptr, msg);
  }

  public String secretDecrypt(String enc_msg) {
    return secretDecrypt(this.ptr, enc_msg);
  }
  public String secretEncrypt(String msg) {
    return secretEncrypt(this.ptr, msg);
  }

  public void printTest(String pk) {
    printTest(this.ptr, pk);
  }

  private final native long initCppSide();

  private native String nonce(long ptr);
  private native void setRemoteNonce(long ptr, String rn);
  private native void genNewNonce(long ptr);

  private native String publicKey(long ptr);
  private native String secretKey(long ptr);
  private native void setRemoteKey(long ptr, String rk);
  private native void genNewKeys(long ptr);

  private native String secret(long ptr);
  private native void setSecret(long ptr, String ns);
  private native void genNewSecret(long ptr);

  private native String publicDecrypt(long ptr, String enc_msg);
  private native String publicEncrypt(long ptr, String msg);

  private native String secretDecrypt(long ptr, String enc_msg);
  private native String secretEncrypt(long ptr, String msg);

  private native void printTest(long ptr, String pk);

  private static int runTests() {
    JaCl sender = new JaCl();
    JaCl receiver = new JaCl();
    
    sender.setRemoteNonce(receiver.nonce());
    receiver.setRemoteNonce(sender.nonce());
    
    sender.setRemoteKey(receiver.publicKey());
    receiver.setRemoteKey(sender.publicKey());
    
    receiver.setSecret(sender.secret());

    System.out.println("Testing Public Encryption");
    
    String message = "This is a public encryption test message.";
    System.out.println("Test Message: " + message);

    String encrypted_message = sender.publicEncrypt(message);
    System.out.println("Encrypted Message: " + encrypted_message);

    String decrypted_message = receiver.publicDecrypt(encrypted_message);
    System.out.println("Decrypted Message: " + decrypted_message);

    if (decrypted_message.equals(message)) {
      System.out.println("Public encryption test successful!");
    }
    else {
      System.out.println("Public encryption test failed!");
      return 1;
    }

    System.out.println("\nTesting Secret Encryption");

    message = "This is a secret encryption test message.";
    System.out.println("Test Message: " + message);

    encrypted_message = receiver.publicEncrypt(message);
    System.out.println("Encrypted Message: " + encrypted_message);

    decrypted_message = sender.publicDecrypt(encrypted_message);
    System.out.println("Decrypted Message: " + decrypted_message);

    if (decrypted_message.equals(message)) {
      System.out.println("Secret encryption test successful!");
    }
    else {
      System.out.println("Secret encryption test failed!");
      return 1;
    }

    return 0;
  }

  public static void main(String[] args) {
    System.exit(runTests());
  }
}

