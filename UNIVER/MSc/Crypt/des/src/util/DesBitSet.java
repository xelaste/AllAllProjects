package util;
import java.util.BitSet;


public class DesBitSet extends BitSet 
{

private BitSet m_bitSet;
private int m_length;

public static DesBitSet bytes2BitSet (byte[] bytes)
{
	    int size = bytes.length * Byte.SIZE;
	    DesBitSet bits = new DesBitSet( size );
   	    
	    for (int i =0;i < bytes.length;i++)
   	    {
   	    	byte b = bytes [i];
   	    	int singleBitMask = 0x80;
   	    	for ( int j = 0 ; j<Byte.SIZE ;j++ )
   	    	{
   	    		int mask = ( singleBitMask >> j );
   	    		if ( ( b & mask ) > 0 )
   	    			bits.set(  i * Byte.SIZE + j  );
   	    	}
   	    	
   	    }
	    
	    return  bits;
}
public DesBitSet ()
{
	m_bitSet = new BitSet();
	m_length = 0;
}

public 	DesBitSet ( BitSet set )
{
	m_bitSet = set;
	m_length = set.size();
}

public 	DesBitSet ( BitSet set , int length )
{
	m_bitSet = set;
	m_length = length;
}

public 	DesBitSet ( DesBitSet set  )
{
     
	if ( set != null )
	{
		m_bitSet = new BitSet( set.paddedLength() );
		m_length = set.paddedLength();
		for (int i=0;i<m_length;i++)
		{
			m_bitSet.set(i,set.get(i) );
		}
	}
	else
	{
		m_bitSet = new BitSet( );
		m_length = 0;
		
	}
			
}

public 	DesBitSet ( int length )
{
	m_bitSet = new BitSet ( length );
	m_length = length;
}

public void and(BitSet set) {
	m_bitSet.and(set);
}

public void and(DesBitSet set) {
	if (set != null )
		m_bitSet.and( set.m_bitSet );
}

public void andNot(BitSet set) {
	m_bitSet.andNot(set);
}

public void andNot(DesBitSet set) {
	if (set != null )
		m_bitSet.andNot( set.m_bitSet );
}

public int cardinality() {
	return m_bitSet.cardinality();
}

public void clear() {
	m_bitSet.clear();
}

public void clear(int fromIndex, int toIndex) {
	m_bitSet.clear(fromIndex, toIndex);
}

public void clear(int bitIndex) {
	m_bitSet.clear(bitIndex);
}

public Object clone() {
	return m_bitSet.clone();
}

public boolean equals(Object obj) {
	return m_bitSet.equals(obj);
}

public void flip(int fromIndex, int toIndex) {
	m_bitSet.flip(fromIndex, toIndex);
}

public void flip(int bitIndex) {
	m_bitSet.flip(bitIndex);
}

public BitSet get(int fromIndex, int toIndex) {
	return m_bitSet.get(fromIndex, toIndex);
}

public boolean get(int bitIndex) {
	return m_bitSet.get(bitIndex);
}

public int hashCode() {
	return m_bitSet.hashCode();
}

public boolean intersects(BitSet set) {
	return m_bitSet.intersects(set);
}

public boolean intersects(DesBitSet set) {
	if (set==null)
		return false;
	else
		return m_bitSet.intersects(set.m_bitSet);
}

public boolean isEmpty() {
	return m_bitSet.isEmpty();
}

public int length() {
	return m_bitSet.length();
}

public int nextClearBit(int fromIndex) {
	return m_bitSet.nextClearBit(fromIndex);
}

public int nextSetBit(int fromIndex) {
	return m_bitSet.nextSetBit(fromIndex);
}

public void or(BitSet set) {
	m_bitSet.or(set);
}

public void or(DesBitSet set) {
	if (set != null )
		m_bitSet.or(set.m_bitSet );
}

public void set(int bitIndex, boolean value) {
	m_bitSet.set(bitIndex, value);
}

public void set(int fromIndex, int toIndex, boolean value) {
	m_bitSet.set(fromIndex, toIndex, value);
}

public void set(int fromIndex, int toIndex) {
	m_bitSet.set(fromIndex, toIndex);
}

public void set(int bitIndex) {
	m_bitSet.set(bitIndex);
}

public int size() {
	return m_bitSet.size();
}

public String toString() {
	return m_bitSet.toString();
}

public void xor(BitSet set) 
{
	m_bitSet.xor( set );
}

public void xor(DesBitSet set) 
{
    if (set != null )	
	m_bitSet.xor( set.m_bitSet );
}

public DesBitSet lrotate ( int steps )
{
	int length = paddedLength();
	BitSet firstBits = get(0, steps );
	
	for (int i=0; i < length ; i++ )
	{
		if ( i < length - steps )
		{
			set (i, get ( i + steps ) );
		}
		else 
		{
			set (i, firstBits.get ( length - ( i + 1 ) ) );
		}
	}
	return this;
}
public int paddedLength ()
{
	return m_length;
}

public DesBitSet append ( DesBitSet  what  )
{
    int len = what.paddedLength();
    int start = paddedLength(); 
	for (int i=0;i<len;i++) 
	{
		set( start + i, what.get (i) );
	}
	m_length += len;
	return this;
}
public byte[] bitSet2Bytes ()
{
    int output_size =  paddedLength()/ Byte.SIZE;
    if ( output_size * Byte.SIZE < paddedLength() )
    	output_size++;
	byte [] output = new byte[ output_size ];
     
	for (int i = 0; i < output.length; i++) 
	{
		 for( int j=0;j<Byte.SIZE;j++ )
		 {
			 output[i] = (byte) ( ( output[i] << 1 ) 
					  |
					  ( get( i * Byte.SIZE +  j  )  ? 1: 0 )  );
		 }
	}
     return output;
}

}
