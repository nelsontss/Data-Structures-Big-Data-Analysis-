package engine;
import java.util.ArrayList;
public class myUser
{
    // variáveis de instância - substitua o exemplo abaixo pelo seu próprio
    private String id;
    private String name;
    private String aboutme;
    private int questions;
    private int answers;
    private int totalposts;
    private int reputation;
    private ArrayList <MyPost> lastposts;

    /**
     * COnstrutor para objetos da classe user
     */
    public myUser()
    {
        this.id="";
        this.name="";
        this.aboutme="";
        this.questions=0;
        this.answers=0;
        this.totalposts=0;
        this.reputation=0;
        this.lastposts=new ArrayList<>();
    }

    public myUser(String id, String name,String aboutme,int questions,int answers,int totalposts,int reputation,ArrayList <MyPost> lastposts)
    {
    this.id=id;
    this.name=name;
    this.aboutme=aboutme;
    this.questions=questions;
    this.answers=answers;
    this.totalposts=totalposts;
    this.reputation=reputation;
    this.lastposts = new ArrayList<>();
    for(MyPost s: lastposts)
                this.lastposts.add(s);
    }
    public myUser (myUser User){
    this.id=User.getId();
    this.name=User.getName();
    this.aboutme=User.getAboutMe();
    this.questions=User.getQuestions();
    this.answers=User.getAnswers();
    this.totalposts=User.getTotalPosts();
    this.reputation=User.getReputation();
    this.lastposts=User.getLastPosts(); 
    }
    
    
    public String getId(){
    return this.id;
    }
    
    
    public String getName(){
    return this.name;
    }
    
    
    public String getAboutMe(){
    return this.aboutme;
    }
    
    
    public int getQuestions(){
    return this.questions;
    }
    
    
    public int getAnswers(){
    return this.answers;
    }
    
    
    public int getTotalPosts(){
    return this.totalposts;
    }
    
    
    public int getReputation(){
    return this.reputation;
    }
    
    
    public ArrayList<MyPost> getLastPosts(){
            ArrayList<MyPost> r = new ArrayList<MyPost>();
            
            for(MyPost s: this.lastposts){
                MyPost x = (MyPost) s;
                r.add(x.clone());
            }
            return r;
    }
    
    
    public void setId(String id){

        this.id=id;
    }
    
    
    public void setName(String Name){
    this.name=name;
    }


    public void setAboutMe (String aboutme){
    this.aboutme=aboutme;
    }
    
    
    public void setReputation(int reputation){
    this.reputation=reputation;
    }
    
    
    public void setQuestions(int questions){
    this.questions=questions;
    }
    
    
    public void setAnswers(int answers){
    this.answers=answers;
    }
    
    
    public void setTotalPosts(int totalposts){
    this.totalposts=totalposts;
    }
    
    
    public void setLastPosts(ArrayList<MyPost> lastposts){
        this.lastposts=new ArrayList<MyPost>();
        for(MyPost s: lastposts)
                this.lastposts.add(s);
    }
    
    public void aumentaAnswers(){
        this.answers++;
        this.totalposts++;
    } 
    
    public void aumentaQuestions(){
        this.questions++;
        this.totalposts++;
    }

    public void addLastPost(MyPost p){
        if(this.lastposts.size()<10){
            this.lastposts.add(p);
        }else{
            if(this.lastposts.get(this.lastposts.size()-1).getData().compareTo(p.getData())>0){
                this.lastposts.set(this.lastposts.size()-1,p);
            }

        }
        this.lastposts.sort(new ComparadorPostsPorData());
    }
        
    public myUser clone() {
        return new myUser(this); 
    }
}
