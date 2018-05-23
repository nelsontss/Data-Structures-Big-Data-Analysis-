import java.util.HashMap;
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
    private HashMap<String,myPost> posts;
    private HashMap<String,String> tags;
    
    public GestStackOverflowModel(){
        this.users = new HashMap<String,myUser>();
        this.posts = new HashMap<String,myPost>();
        this.tags = new HashMap<String,String>();
    }
    
    public void addUser(myUser u){
        this.users.put(u.getId(),u);
    }
    
    public void addPost(myPost p){
        this.posts.put(p.getId(),p);
    }
    
    public void addTag(String name, String id){
        this.tags.put(name,id);
    }
    
}
