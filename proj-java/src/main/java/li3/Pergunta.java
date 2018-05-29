import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;
import java.time.LocalDate;
/**
 * Write a description of class Pergunta here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Pergunta extends MyPost
{
    // instance variables - replace the example below with your own
    private String title;
    private ArrayList<String> tags;
    private ArrayList<Resposta> resp;
    private HashMap<String,Resposta> respHash;
    private int answerCount;

    /**
     * Constructor for objects of class Pergunta
     */
    public Pergunta()
    {
        // initialise instance variables
        super();
        this.title="";
        this.tags= new ArrayList<>();
        this.resp= new ArrayList<>();
        this.respHash= new HashMap<>();
        this.answerCount=0;
    }

    public Pergunta(String title, ArrayList<String> tags, ArrayList<Resposta> resp, 
    HashMap<String,Resposta> respHash, int ac, String id, String ownerUser,LocalDate data)
    {
        // initialise instance variables
        super(id, ownerUser, data);
        this.title=title;
        setTags(tags);
        setResp(resp);
        setRespHash(respHash);
        this.answerCount=ac;
    }
    
    public Pergunta(Pergunta p)
    {
        // initialise instance variables
        super(p);
        this.title=p.getTitle();
        this.tags= p.getTags();
        this.resp= p.getResp();
        this.respHash= p.getRespHash();
        this.answerCount=p.getAnswerCount();
    }
    //gets & sets
    public String getTitle(){
        return this.title;
    }
    
    public ArrayList<String> getTags(){
        ArrayList<String> res = new ArrayList<String>();
        for(String s: this.tags)
            res.add(s);
        return res;
    }
    
    public ArrayList<Resposta> getResp(){
        ArrayList<Resposta> res = new ArrayList<Resposta>();
        for(Resposta r: this.resp)
            res.add(r.clone());
        return res;
    }
    
    public HashMap<String,Resposta> getRespHash(){
        HashMap<String,Resposta> res= new HashMap<String,Resposta>();
        for(Map.Entry<String,Resposta> sr: this.respHash.entrySet())
            res.put(sr.getKey(),sr.getValue().clone());
        return res;
    }
    
    public int getAnswerCount(){
        return this.answerCount;
    }
    
    public void setTags(ArrayList<String> tags){
        this.tags= new ArrayList<String>();
        for(String s: tags){
            this.tags.add(s);
        }
    }
    
    public void setRespHash(HashMap<String,Resposta> respHash){
        this.respHash= new HashMap<String,Resposta>();
        for(Map.Entry<String,Resposta> r: respHash.entrySet())
            this.respHash.put(r.getKey(), r.getValue().clone());
    }
    
    public void setResp(ArrayList<Resposta> resp){
        this.resp= new ArrayList<Resposta>();
        for(Resposta r: resp)
            this.resp.add(r.clone());
    }
    
    public void setAnswerCount(int ac){
        this.answerCount=ac;
    }
    
    public Pergunta clone(){
        return new Pergunta(this);
    }
    
    public boolean equals(Object o){
        if(this==o) return true;
        if(o==null && this.getClass()!=o.getClass()) return false;
        Pergunta p= (Pergunta) o;
        return (this.title.equals(p.getTitle()) && this.tags.equals(p.getTags())
        && this.resp.equals(p.getResp()) && this.respHash.equals(p.getRespHash()));
    }
    
    public String toString(){
        StringBuilder sb= new StringBuilder(super.toString());
        sb.append("\nTitulo: ");sb.append(this.title);
        sb.append("\nTags: ");sb.append(this.tags.toString());
        sb.append("\nNumero de respostas: ");sb.append(this.answerCount);
        sb.append("\nRespostas: ");sb.append(this.resp.toString());
        sb.append("\nId da Resposta e respetiva Resposta: ");sb.append(this.respHash.toString());
        return sb.toString();
    }
}
