package engine;

import java.util.*;
import java.time.LocalDate;
import java.io.FileNotFoundException;
import javax.swing.*;
import javax.xml.stream.XMLStreamException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;
import java.util.stream.Collectors;
import java.util.HashMap;
import java.util.Map;
import common.Pair;
/**
 * Write a description of class Estrutura Principal here.
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
    private ArrayList<myUser> usersByNPosts;
    private ArrayList<myUser> usersByReputation;
    private long totalAnswers;
    private long totalQuestions;
    private long totalPosts;
    
    public GestStackOverflowModel(){
        this.users = new HashMap<String,myUser>();
        this.posts = new HashMap<String,MyPost>();
        this.tags = new HashMap<>();
        this.usersByNPosts = new ArrayList<>();
        this.usersByReputation = new ArrayList<>();
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
        ArrayList<MyPost> aux = this.postsList.get(17-(year-2000)).get(12-month).get(31-day);
        aux.add(p);
        myUser u = users.get(p.getOwnerUser());
        u.addLastPost(p);
        if(p instanceof Resposta){
            Resposta r = (Resposta) p;
            Pergunta parent = (Pergunta)this.posts.get(r.getParentID());
            this.totalAnswers++;
            this.totalPosts++;
            u.aumentaAnswers();
            parent.addResp(r);
            r.calc_post_pont(u.getReputation());
        }else{
            this.totalQuestions++;
            this.totalPosts++;
            ArrayList<MyPost> aux1 = this.questionsList.get(17-(year-2000)).get(12-month).get(31-day);
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
        this.usersByReputation.sort(new ComparadorUsersPorReputation());
        this.usersByNPosts.sort(new ComparadorUsersPorPosts());
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
        for(int i = 17-(end.getYear()-2000); i<= 17-(begin.getYear()-2000); i++){
            if(i == 0) j1 = end.getMonthValue(); else j1 = 12;
            if(i == 17-(begin.getYear()-2000)) j2 = begin.getMonthValue(); else j2 = 1;
            for(int a = 12-j1; a <= 12-j2; a++){
                if(a==0) l1 = end.getDayOfMonth(); else l1  = 31;
                if(a==12-begin.getMonthValue()) l2 = begin.getDayOfMonth(); else l2  = 1;
                for (int k = 31-l1; k<=31-l2; k++ ){
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
                for(int i = 17-(end.getYear()-2000); i<= 17-(begin.getYear()-2000); i++){
                    if(i == 0) j1 = end.getMonthValue(); else j1 = 12;
                    if(i == 17-(begin.getYear()-2000)) j2 = begin.getMonthValue(); else j2 = 1;
                    for(int a = 12-j1; a <= 12-j2; a++){
                        if(a==0) l1 = end.getDayOfMonth(); else l1  = 31;
                        if(a==12-begin.getMonthValue()) l2 = begin.getDayOfMonth(); else l2  = 1;
                        for (int k = 31-l1; k<=31-l2; k++ ){
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


    public List<Long> containsWord(int N, String word){
        List<Long> r = new ArrayList<>();
        Iterator<ArrayList<ArrayList<ArrayList<MyPost>>>> i = questionsList.iterator();
        int x = 0 ;
        while (i.hasNext() && x<N){
            Iterator<ArrayList<ArrayList<MyPost>>> k = i.next().iterator();
            while (k.hasNext() && x<N){
                Iterator<ArrayList<MyPost>> j = k.next().iterator();
                while (j.hasNext() && x<N){
                    Iterator<MyPost> o = j.next().iterator();
                    while(o.hasNext() && x<N){
                        Pergunta p1 = (Pergunta) o.next();
                        if(p1.getTitle().contains(word)){
                            r.add(Long.valueOf(p1.getID()));
                            x++;
                        }
                    }
                }
            }
        }
        return r;
    }

    public List<Long> bothParticipated(int N, long id1, long id2){
        List<Long> r = new ArrayList<>();
        Iterator<ArrayList<ArrayList<ArrayList<MyPost>>>> i = questionsList.iterator();
        int x = 0 ;
        while (i.hasNext() && x<N){
            Iterator<ArrayList<ArrayList<MyPost>>> k = i.next().iterator();
            while (k.hasNext() && x<N){
                Iterator<ArrayList<MyPost>> j = k.next().iterator();
                while (j.hasNext() && x<N){
                    Iterator<MyPost> o = j.next().iterator();
                    while(o.hasNext() && x<N){
                        Pergunta p1 = (Pergunta) o.next();
                        if(p1.bothParticipated(id1,id2)){
                            r.add(Long.valueOf(p1.getID()));
                            x++;
                        }
                    }
                }
            }
        }
        return r;
    }

    public long betterAnswer(long id){
        String x = String.valueOf(id);
        MyPost p = posts.get(x);
        if(p instanceof Pergunta){
            Pergunta y = (Pergunta) p;
            return Long.parseLong(y.getBestAnswer());
        }else
            return -1;
    }

    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
        List<Long> r = new ArrayList<>();
        HashMap<String,Integer> aux = new HashMap<>();
        HashMap<String,myUser> topN = new HashMap<>();
        for(int i = 0; i<N; i++){
            topN.put(usersByReputation.get(i).getId(),usersByReputation.get(i));
        }

        int l1;
        int l2;
        int j1;
        int j2;
        for(int i = 17-(end.getYear()-2000); i<= 17-(begin.getYear()-2000); i++){
            if(i == 0) j1 = end.getMonthValue(); else j1 = 12;
            if(i == 17-(begin.getYear()-2000)) j2 = begin.getMonthValue(); else j2 = 1;
            for(int a = 12-j1; a <= 12-j2; a++){
                if(a==0) l1 = end.getDayOfMonth(); else l1  = 31;
                if(a==12-begin.getMonthValue()) l2 = begin.getDayOfMonth(); else l2  = 1;
                for (int k = 31-l1; k<=31-l2; k++ ){
                    for(MyPost p : this.questionsList.get(i).get(a).get(k)){
                        Pergunta v= (Pergunta) p;
                        if (topN.containsKey(v.getOwnerUser())){
                            for(String s: v.getTags()) {
                                if(aux.containsKey(s)){
                                    aux.put(s,aux.get(s)+1);
                                }else aux.put(s,1);
                            }
                        }
                    }
                }
            }
        }

        List<String> aux2 = aux.keySet().stream()
                                        .sorted((v1,v2)-> -1 * aux.get(v1).compareTo(aux.get(v2)))
                                        .collect(Collectors.toList());
        for (String s : aux2)
            r.add(Long.parseLong(tags.get(s)));

        return r;
    }
}    
    

