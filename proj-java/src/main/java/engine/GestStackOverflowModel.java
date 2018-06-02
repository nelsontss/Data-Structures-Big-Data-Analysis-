import java.util.*;
import java.time.LocalDate;
import java.io.FileNotFoundException;
import javax.xml.stream.XMLStreamException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;
import java.util.stream.Collectors;
import java.util.HashMap;
import java.util.Map;

import common.Pair;
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
        this.tags = new HashMap<>();
        this.usersByNPosts = new TreeSet<myUser>(new ComparadorUsersPorPosts());
        this.usersByReputation = new TreeSet<myUser>(new ComparadorUsersPorReputation());
        this.postsList = new ArrayList<>(18);
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





    public Pair<String,String> infoFromPost(long id){
        Pair<String,String> r = new Pair("","");
        if (this.users.containsKey(id)){
             MyPost a=this.posts.get(id);
             if (a instanceof Pergunta){
                Pergunta p = (Pergunta) a;
                String l =p.getTitle();
                myUser b =this.users.get(p.getOwnerUser());
                String m=b.getName();
                r =  new Pair(l,m);
                
             }
             if (a instanceof Resposta){
                Resposta p = (Resposta) a;
                MyPost d=this.posts.get(p.getParentID());
                String v=(p.getParentID());
                Pergunta ç= (Pergunta) d;
                String z= ç.getTitle();
                r =  new Pair(v,z);
             }
        }
        return r;
    }

    public List<Long> topMostActive(int N){
        List<Long> list = new ArrayList<Long>();
        list=this.usersByNPosts.stream()
                .limit(N)
                .map(e->Long.valueOf(e.getId()))
                .collect(Collectors.toList());
        return list;
    }

    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
        int l1;
        int l2; 
        int j1;
        int j2;
        long resp = 0;
        long perg = 0;
        for(int i = begin.getYear()-2000; i<= end.getYear()-2000; i++){
            if(i == 0) j1 = begin.getMonthValue(); else j1 = 1;
            if(i == end.getYear()-2000) j2 = end.getMonthValue(); else j2 = 12;
            for(int a = j1; a <=j2; a++){
                if(a==0) l1 = begin.getDayOfMonth(); else l1  = 1;
                if(a==end.getMonthValue()) l2 = end.getDayOfMonth(); else l2  = 31;
                for (int k = l1; k<=l2; k++ ){
                    for(MyPost p : this.postsList.get(i).get(a).get(k)){
                        if(p instanceof Resposta)
                            resp++;
                        if(p instanceof Pergunta)
                            perg++;
                    }
                }
            }
        }
        return new Pair(perg,resp);
    }

public Pair<String, List<Long>> getUserInfo(long id){
myUser c=users.get(id);
List m=new ArrayList<Long>();
m=c.getLastPosts().stream().limit(10).collect(Collectors.toList());  
String k= c.getAboutMe();
return new Pair (k,m);
}

public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
List t=new ArrayList <Long>();
int l1;
int l2; 
int j1;
int j2;    
        for(int i = begin.getYear()-2000; i<= end.getYear()-2000; i++){
            if(i == 0) j1 = begin.getMonthValue(); else j1 = 1;
            if(i == end.getYear()-2000) j2 = end.getMonthValue(); else j2 = 12;
            for(int a = j1; a <=j2; a++){
                if(a==0) l1 = begin.getDayOfMonth(); else l1  = 1;
                if(a==end.getMonthValue()) l2 = end.getDayOfMonth(); else l2  = 31;
                for (int k = l1; k<=l2; k++ ){
                    for(MyPost p : this.questionsList.get(i).get(a).get(k)){ 
                        Pergunta v= (Pergunta) p;
                        if (v.getTags().contains(tag)){
                        t.add(v.getID());
                        }
                    }
                }
            }
        }     
 return t;
   }
}    
    

