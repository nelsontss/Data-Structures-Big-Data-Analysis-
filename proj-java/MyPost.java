import java.time.LocalDate;
import java.util.Iterator;
/**
 * Write a description of class MyPost here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class MyPost
{
    // instance variables - replace the example below with your own
    private String id;
    private String ownerUser;
    private LocalDate data;
    

    /**
     * Constructor for objects of class MyPost
     */
    public MyPost()
    {
        // initialise instance variables
        this.id ="";
        this.ownerUser="";
        this.data= LocalDate.now();
    }
    
    public MyPost(String id, String ou, LocalDate data)
    {
        this.id =id;
        this.ownerUser=ou;
        this.data= data;
    }
    
    public MyPost(MyPost mp)
    {
        this.id =mp.getID();
        this.ownerUser=mp.getOwnerUser();
        this.data= mp.getData();
    }
    
    //gets & sets

    public String getID(){
        return this.id;
    }
    
    public String getOwnerUser(){
        return this.ownerUser;
    }
    
    public LocalDate getData(){
        return this.data;
    }
    
    public void setID(String id){
        this.id=id;
    }
    
    public void setOwnerUser(String ou){
        this.ownerUser=ou;
    }
    
    public void setData(LocalDate data){
        this.data=data;
    }
    
    public MyPost clone(){
        return new MyPost(this);
    }
    
    public boolean equals(Object o){
        if(this==o) return true;
        if(o==null && this.getClass()!=o.getClass()) return false;
        MyPost mp= (MyPost) o;
        return (this.id.equals(mp.getID()) && this.ownerUser.equals(mp.getOwnerUser())
        && this.data.equals(mp.getData()));
    }
    
    public String toString(){
        StringBuilder sb= new StringBuilder();
        sb.append("ID do post: ");sb.append(this.id);
        sb.append("ID do proprietario do post: ");sb.append(this.ownerUser);
        sb.append("Data do post: ");sb.append(this.data);
        return sb.toString();
    }
}
