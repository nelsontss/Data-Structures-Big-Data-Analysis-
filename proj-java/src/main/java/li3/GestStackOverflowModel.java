import java.util.HashMap;
import java.util.Map;
import java.time.LocalDate;
import java.util.List;
import java.util.ArrayList;
import java.util.TreeSet;
import java.io.FileNotFoundException;
import javax.xml.stream.XMLStreamException;
/**
 * Write a description of class EstruturaPrincipal here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class GestStackOverflowModel 
{
    // instance variables - replace the example below with your own
    private HashMap<String,myUser> users;
    private HashMap<String,MyPost> posts;
    private HashMap<String,String> tags;
    private ArrayList<ArrayList<ArrayList<ArrayList<MyPost>>>> postsList;
    private ArrayList<ArrayList<ArrayList<ArrayList<MyPost>>>> questionsList;
    private TreeSet<myUser> usersByNPosts;
    private TreeSet<myUser> usersByReputation;
    private long totalAnswers;
    private long totalQuestions;
    private long totalPosts;
    
    public GestStackOverflowModel(){
        this.users = new HashMap<String,myUser>();
        this.posts = new HashMap<String,MyPost>();
        this.tags = new HashMap<String,String>();
        this.usersByNPosts = new TreeSet<myUser>(new ComparadorUsersPorPosts());
        this.usersByReputation = new TreeSet<myUser>(new ComparadorUsersPorReputation());
        this.postsList = new ArrayList<ArrayList<ArrayList<ArrayList<MyPost>>>>(18);
        this.totalAnswers = 0;
        this.totalQuestions = 0;
        this.totalPosts = 0;
    }
    
    public void addUser(myUser u) {
        this.users.put(u.getId(), u);
        this.usersByNPosts.add(u);
        this.usersByReputation.add(u);
    }
    
    public void addPost(MyPost p){
        this.posts.put(p.getID(),p);
        int year = p.getData().getYear();
        int month = p.getData().getMonthValue();
        int day  = p.getData().getDayOfMonth();
        ArrayList<MyPost> aux = this.postsList.get(year-2000).get(month).get(day);
        aux.add(p);
        if(p instanceof Resposta){
            Resposta r = (Resposta) p;
            Pergunta parent = (Pergunta)this.posts.get(r.getParentID());
            myUser u = this.users.get(p.getOwnerUser());
            this.totalAnswers++;
            this.totalPosts++;
            u.aumentaAnswers();
            parent.addResp(r);
            r.calc_post_pont(u.getReputation());
        }else{
            this.totalQuestions++;
            this.totalPosts++;
            ArrayList<MyPost> aux1 = this.questionsList.get(year-2000).get(month).get(day);
            aux1.add(p);
            this.users.get(p.getOwnerUser()).aumentaQuestions();
        }
    }
    
    public void addTag(String name, String id){
        this.tags.put(name,id);
    }
    
    public void load(String dump) throws XMLStreamException, FileNotFoundException{
        Parser p = new Parser(this);
        p.parseUsers(dump);
        p.parsePosts(dump);
        p.parseTags(dump);
    }
    
    
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        
        for(Map.Entry<String,MyPost> me: posts.entrySet()){
            sb.append("\n"+me.getKey().toString());
            sb.append("\n"+me.getValue().toString());
        }
        
        return sb.toString();
    }
}
