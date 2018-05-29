import java.util.HashMap;
import java.util.Map;
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
    
    public GestStackOverflowModel(){
        this.users = new HashMap<String,myUser>();
        this.posts = new HashMap<String,MyPost>();
        this.tags = new HashMap<String,String>();
    }
    
    public void addUser(myUser u){
        this.users.put(u.getId(),u);
    }
    
    public void addPost(MyPost p){
        this.posts.put(p.getID(),p);
    }
    
    public void addTag(String name, String id){
        this.tags.put(name,id);
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
