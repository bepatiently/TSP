package source;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Arrays;
import java.util.Collections;

public class file  {
       
	
      
    public static void main(String a[]) throws Throwable, IOException{
    	 String line= "    ";
         List <cities> list= new ArrayList();
    	
    	
    	BufferedReader bfr = new BufferedReader(new FileReader("D:\\pc\\Masaüstü\\dersler\\Automata Theory\\Project\\att48_xy.txt"));
    	
        while((line=bfr.readLine())!=null) {
        	String s[]=line.split("    ");
        	cities ct=new cities(Integer.parseInt(s[0]),Integer.parseInt(s[1]));
        	list.add(ct);
        	
        } 
         
        cities ct=new cities(400,300);
        List<cities> dt=new ArrayList();
        dt=cities.calcDistance(list,ct);
       Collections.sort(dt);
        
        int c=0;
        while (c<4) {
        	System.out.println(dt.get(c));
        	c++;
        }
    
    	
    	
    	
    }
}















