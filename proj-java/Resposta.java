import java.time.LocalDate;
/**
 * Write a description of class Resposta here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Resposta extends MyPost
{
    // instance variables - replace the example below with your own
    private String parentID;
    private int comments;
    private int score;
    private float pont;
    
    /**
     * Constructor for objects of class Resposta
     */
    public Resposta()
    {
        // initialise instance variables
        super();
        this.parentID="";
        this.comments=0;
        this.score=0;
        this.pont=0;
    }
    
    public Resposta(String pID, int comm, int score, float pont, String id, String ownerUser, LocalDate data)
    {
        // initialise instance variables
        super(id,ownerUser, data);
        this.parentID=pID;
        this.comments=comm;
        this.score=score;
        this.pont=pont;
    }

    public Resposta(Resposta r1)
    {
        // initialise instance variables
        super(r1);
        this.parentID=r1.getParentID();
        this.comments=r1.getNComments();
        this.score=r1.getScore();
        this.pont=r1.getPont();
    }
    
    //gets & sets
    
    public String getParentID(){
        return this.parentID;
    }
    
    public int getNComments(){
        return this.comments;
    }
    
    public int getScore(){
        return this.score;
    }
    
    public float getPont(){
        return this.pont;
    }
    
    public void setParentID(String pID){
        this.parentID=pID;
    }
    
    public void setNComments(int comm){
        this.comments=comm;
    }
    
    public void setScore(int score){
        this.score=score;
    }
    
    public void setPont(float pont){
        this.pont=pont;
    }
    
    public boolean equals(Object o){
        if(this==o) return true;
        if(o==null && this.getClass()!=o.getClass()) return false;
        
        Resposta r= (Resposta) o;
        return(this.getParentID().equals(r.getParentID()) && this.getNComments() == r.getNComments()
        && this.getScore() == r.getScore() && this.getPont() == r.getPont());
    }
    
    public String toString(){
        StringBuilder sb = new StringBuilder(super.toString());
        sb.append("Id da pergunta: ");sb.append(this.parentID);
        sb.append("Numero de comentarios: ");sb.append(this.comments);
        sb.append("Score: ");sb.append(this.score);
        sb.append("Pontuaçao: ");sb.append(this.pont);
        return sb.toString();
    }
    
    public Resposta clone(){
        return new Resposta(this);
    }
}
