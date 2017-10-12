package com.fulong.portal.servlet;

import java.io.PrintWriter;

/**
 * <p>Title: 龙驭门户引擎</p>
 *
 * <p>Description: 龙驭网站内容管理系统核心引擎</p>
 *
 * <p>Copyright: 北京中科辅龙计算机技术股份有限公司</p>
 *
 * <p>Company: 北京中科辅龙计算机技术股份有限公司</p>
 *
 * @author Lixf
 * @version 1.0
 */
public class LockablePrintWriter extends PrintWriter {
    private PrintWriter out;
    private boolean locked;
    public LockablePrintWriter(PrintWriter out) {
        super(out);
        this.out = out;
        this.locked = false;
    }

    public void setLock(boolean locked){
        this.locked=locked;
    }
    public void flush() {
        out.flush();
    }
    /*
     * Exception-catching, synchronized output operations,
     * which also implement the write() methods of Writer
     */

    /**
     * Write a single character.
     * @param c int specifying a character to be written.
     */
    public void write(int c) {
        if (!locked)
            out.write(c);
    }

    /**
     * Write A Portion of an array of characters.
     * @param buf Array of characters
     * @param off Offset from which to start writing characters
     * @param len Number of characters to write
     */
    public void write(char buf[], int off, int len) {
        if (!locked)
            out.write(buf, off, len);
    }


    /**
     * Write a portion of a string.
     * @param s A String
     * @param off Offset from which to start writing characters
     * @param len Number of characters to write
     */
    public void write(String s, int off, int len) {
        if (!locked)
            out.write(s, off, len);
    }

    /**
     * Print a string.  If the argument is <code>null</code> then the string
     * <code>"null"</code> is printed.  Otherwise, the string's characters are
     * converted into bytes according to the platform's default character
     * encoding, and these bytes are written in exactly the manner of the
     * <code>{@link #write(int)}</code> method.
     *
     * @param      s   The <code>String</code> to be printed
     */
    public void print(String s) {
        if (!locked)
            out.print(s);
    }

    /**
     * Print an object.  The string produced by the <code>{@link
     * java.lang.String#valueOf(Object)}</code> method is translated into bytes
     * according to the platform's default character encoding, and these bytes
     * are written in exactly the manner of the <code>{@link #write(int)}</code>
     * method.
     *
     * @param      obj   The <code>Object</code> to be printed
     * @see        java.lang.Object#toString()
     */
    public void print(Object obj) {
        if (!locked)
            out.print(obj);
    }

    /* Methods that do terminate lines */

    /**
     * Terminate the current line by writing the line separator string.  The
     * line separator string is defined by the system property
     * <code>line.separator</code>, and is not necessarily a single newline
     * character (<code>'\n'</code>).
     */
    public void println() {
        if (!locked)
            out.println();
    }


    /**
     * Print a String and then terminate the line.  This method behaves as
     * though it invokes <code>{@link #print(String)}</code> and then
     * <code>{@link #println()}</code>.
     *
     * @param x the <code>String</code> value to be printed
     */
    public void println(String x) {
        if (!locked)
            out.println(x);
    }

    /**
     * Print an Object and then terminate the line.  This method behaves as
     * though it invokes <code>{@link #print(Object)}</code> and then
     * <code>{@link #println()}</code>.
     *
     * @param x the <code>Object</code> value to be printed
     */
    public void println(Object x) {
        if (!locked)
            out.print(x);
    }

    public void close() {
       out.close();
     }

     /**
      * Flush the stream if it's not closed and check its error state.
      * Errors are cumulative; once the stream encounters an error, this
      * routine will return true on all successive calls.
      *
      * @return True if the print stream has encountered an error, either on the
      * underlying output stream or during a format conversion.
      */
     public boolean checkError() {
       return out.checkError();
     }



     /**
      * Write an array of characters.  This method cannot be inherited from the
      * Writer class because it must suppress I/O exceptions.
      * @param buf Array of characters to be written
      */
     public void write(char buf[]) {
         if(!this.locked)
             out.write(buf);
     }


     /**
      * Write a string.  This method cannot be inherited from the Writer class
      * because it must suppress I/O exceptions.
      * @param s String to be written
      */
     public void write(String s) {
         if(!this.locked)
             out.write(s);
     }

     /* Methods that do not terminate lines */

     /**
      * Print a boolean value.  The string produced by <code>{@link
      * java.lang.String#valueOf(boolean)}</code> is translated into bytes
      * according to the platform's default character encoding, and these bytes
      * are written in exactly the manner of the <code>{@link
      * #write(int)}</code> method.
      *
      * @param      b   The <code>boolean</code> to be printed
      */
     public void print(boolean b) {
         if(!this.locked)
             out.print(b);
     }

     /**
      * Print a character.  The character is translated into one or more bytes
      * according to the platform's default character encoding, and these bytes
      * are written in exactly the manner of the <code>{@link
      * #write(int)}</code> method.
      *
      * @param      c   The <code>char</code> to be printed
      */
     public void print(char c) {
         if(!this.locked)
             out.print(c);
     }

     /**
      * Print an integer.  The string produced by <code>{@link
      * java.lang.String#valueOf(int)}</code> is translated into bytes according
      * to the platform's default character encoding, and these bytes are
      * written in exactly the manner of the <code>{@link #write(int)}</code>
      * method.
      *
      * @param      i   The <code>int</code> to be printed
      * @see        java.lang.Integer#toString(int)
      */
     public void print(int i) {
         if(!this.locked)
             out.print(i);

     }

     /**
      * Print a long integer.  The string produced by <code>{@link
      * java.lang.String#valueOf(long)}</code> is translated into bytes
      * according to the platform's default character encoding, and these bytes
      * are written in exactly the manner of the <code>{@link #write(int)}</code>
      * method.
      *
      * @param      l   The <code>long</code> to be printed
      * @see        java.lang.Long#toString(long)
      */
     public void print(long l) {
         if(!this.locked)
             out.print(l);

     }

     /**
      * Print a floating-point number.  The string produced by <code>{@link
      * java.lang.String#valueOf(float)}</code> is translated into bytes
      * according to the platform's default character encoding, and these bytes
      * are written in exactly the manner of the <code>{@link #write(int)}</code>
      * method.
      *
      * @param      f   The <code>float</code> to be printed
      * @see        java.lang.Float#toString(float)
      */
     public void print(float f) {
         if(!this.locked)
             out.print(f);

     }

     /**
      * Print a double-precision floating-point number.  The string produced by
      * <code>{@link java.lang.String#valueOf(double)}</code> is translated into
      * bytes according to the platform's default character encoding, and these
      * bytes are written in exactly the manner of the <code>{@link
      * #write(int)}</code> method.
      *
      * @param      d   The <code>double</code> to be printed
      * @see        java.lang.Double#toString(double)
      */
     public void print(double d) {
         if(!this.locked)
             out.print(d);

     }

     /**
      * Print an array of characters.  The characters are converted into bytes
      * according to the platform's default character encoding, and these bytes
      * are written in exactly the manner of the <code>{@link #write(int)}</code>
      * method.
      *
      * @param      s   The array of chars to be printed
      *
      * @throws  NullPointerException  If <code>s</code> is <code>null</code>
      */
     public void print(char s[]) {
         if(!this.locked)
             out.print(s);

     }


     /**
      * Print a boolean value and then terminate the line.  This method behaves
      * as though it invokes <code>{@link #print(boolean)}</code> and then
      * <code>{@link #println()}</code>.
      *
      * @param x the <code>boolean</code> value to be printed
      */
     public void println(boolean x) {
         if(!this.locked)
             out.println(x);
     }

     /**
      * Print a character and then terminate the line.  This method behaves as
      * though it invokes <code>{@link #print(char)}</code> and then <code>{@link
      * #println()}</code>.
      *
      * @param x the <code>char</code> value to be printed
      */
     public void println(char x) {
         if(!this.locked)
             out.println(x);
     }

     /**
      * Print an integer and then terminate the line.  This method behaves as
      * though it invokes <code>{@link #print(int)}</code> and then <code>{@link
      * #println()}</code>.
      *
      * @param x the <code>int</code> value to be printed
      */
     public void println(int x) {
         if(!this.locked)
             out.println(x);
     }

     /**
      * Print a long integer and then terminate the line.  This method behaves
      * as though it invokes <code>{@link #print(long)}</code> and then
      * <code>{@link #println()}</code>.
      *
      * @param x the <code>long</code> value to be printed
      */
     public void println(long x) {
         if(!this.locked)
             out.println(x);
     }

     /**
      * Print a floating-point number and then terminate the line.  This method
      * behaves as though it invokes <code>{@link #print(float)}</code> and then
      * <code>{@link #println()}</code>.
      *
      * @param x the <code>float</code> value to be printed
      */
     public void println(float x) {
         if(!this.locked)
             out.println(x);
     }

     /**
      * Print a double-precision floating-point number and then terminate the
      * line.  This method behaves as though it invokes <code>{@link
      * #print(double)}</code> and then <code>{@link #println()}</code>.
      *
      * @param x the <code>double</code> value to be printed
      */
     public void println(double x) {
         if(!this.locked)
             out.println(x);
     }

     /**
      * Print an array of characters and then terminate the line.  This method
      * behaves as though it invokes <code>{@link #print(char[])}</code> and then
      * <code>{@link #println()}</code>.
      *
      * @param x the array of <code>char</code> values to be printed
      */
     public void println(char x[]) {
         if(!this.locked)
             out.println(x);
     }



}
