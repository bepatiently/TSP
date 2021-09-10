package source;

import java.util.*;


public class cities extends file implements Comparable <cities> {
	int Xcord;
	int Ycord;
	double SampleDistance;
	
	
	public cities(int Xcord, int Ycord) {
	    super();
		this.Xcord=Xcord;
		this.Ycord=Ycord;
		
	}
	
	public cities (int Xcord, int Ycord, double SampleDistance) {
		super();
		this.Xcord=Xcord;
		this.Ycord=Ycord;
		this.SampleDistance=SampleDistance;
	}
	
	
	public void setSampleDistance(double SampleDistance) {
		this.SampleDistance=SampleDistance;
		
	}

	public static List calcDistance(List<cities> list, cities ct) {
		for(cities c:list)
		{
			double dx= Math.pow(c.Xcord- ct.Xcord,2);
			double dy= Math.pow(c.Ycord-ct.Ycord,2);
			double distance=Math.sqrt(dx+dy);
			c.setSampleDistance(distance);
			
			
		}
		return list;	
	}

	@Override
	public int compareTo(cities c) {
		
		return (int)((this.SampleDistance-c.SampleDistance));
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}








































































