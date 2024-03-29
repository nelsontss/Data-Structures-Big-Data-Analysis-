package engine;

import common.Pair;
import li3.TADCommunity;

import java.util.*;
import java.time.LocalDate;
import java.io.FileNotFoundException;
import javax.xml.stream.XMLStreamException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.HashMap;
import java.util.Map;
/**
 * Classe que contém a estrutura principal e implementa as querys
 *
 * @author Grupo 48
 * @version 12/06/2018
 */

public class GestStackOverflowModel implements TADCommunity
{
    // instance variables - replace the example below with your own
    private HashMap<String,myUser> users;
    private HashMap<String,MyPost> posts;
    private HashMap<String,String> tags;
    private ArrayList<ArrayList<ArrayList<ArrayList<MyPost>>>> postsList;
    private ArrayList<ArrayList<ArrayList<ArrayList<MyPost>>>> questionsList;
    private ArrayList<myUser> usersByNPosts;
    private ArrayList<myUser> usersByReputation;

    /**
     * Construtor vazio da estrutura principal
     */
    public GestStackOverflowModel(){
        this.users = new HashMap<String,myUser>();
        this.posts = new HashMap<String,MyPost>();
        this.tags = new HashMap<>();
        this.usersByNPosts = new ArrayList<>();
        this.usersByReputation = new ArrayList<>();
        this.postsList = new ArrayList<>(18);
        this.questionsList = new ArrayList<>(18);
        for(int i = 0; i<18; i++){
            this.postsList.add(new ArrayList<>());
            this.questionsList.add(new ArrayList<>());
            for(int i2 = 0; i2<12; i2++){
                this.postsList.get(i).add(new ArrayList<>());
                this.questionsList.get(i).add(new ArrayList<>());
                for(int i3 = 0; i3<31; i3++){
                    this.postsList.get(i).get(i2).add(new ArrayList<>());
                    this.questionsList.get(i).get(i2).add(new ArrayList<>());
                }
            }
        }

    }

    /**
     * Função que adicionar um utilizador às estruturas com utilizadores
     * @param u
     */
    public void addUser(myUser u) {
        this.users.put(u.getId(), u);
        this.usersByNPosts.add(u);
        this.usersByReputation.add(u);
    }

    /**
     * Função que adiciona um post às estruturas com posts
     * @param p Post a adicionar
     */
    public void addPost(MyPost p){
        this.posts.put(p.getID(),p);
        int year = p.getData().getYear();
        int month = p.getData().getMonthValue();
        int day  = p.getData().getDayOfMonth();

        this.postsList.get(17-(year-2000)).get(12-month).get(31-day).add(p);

        myUser u = users.get(p.getOwnerUser());
        u.addLastPost(p);
        if(p instanceof Resposta){
            Resposta r = (Resposta) p;
            r.calc_post_pont(u.getReputation());
            Pergunta parent = (Pergunta)this.posts.get(r.getParentID());

            u.aumentaAnswers();
            if(parent!=null)
            parent.addResp(r);

        }else{

            this.questionsList.get(17-(year-2000)).get(12-month).get(31-day).add(p);
            this.users.get(p.getOwnerUser()).aumentaQuestions();
        }

    }

    /**
     * Função que adiciona uma tag ao map com as tags
     * @param name Nome da tag
     * @param id ID da tag
     */
    public void addTag(String name, String id){

        this.tags.put(name,id);
    }

    /**
     * Função que carrega as estruturas de posts, users e tags
     * @param dump Caminho para os ficheiros xml
     */
    public void load(String dump) {

        try {
            Parser p = new Parser(this);
            p.parseUsers(dump);
            p.parsePosts(dump);
            p.parseTags(dump);
            this.usersByReputation.sort(new ComparadorUsersPorReputation());
            this.usersByNPosts.sort(new ComparadorUsersPorPosts());
        }catch (XMLStreamException e){
            e.printStackTrace();
        }catch (FileNotFoundException e){
            e.printStackTrace();

        }

    }

    /**
     * Função que transforma os pares (id,post) numa string
     * @return String dos pares (id,post)
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        
        for(Map.Entry<String,MyPost> me: posts.entrySet()){
            sb.append("\n"+me.getKey().toString());
            sb.append("\n"+me.getValue().toString());
        }
        
        return sb.toString();
    }




    //query 1
    public Pair<String,String> infoFromPost(long id){
        Pair<String,String> r = new Pair("","");
        if (this.posts.containsKey(String.valueOf(id))){
             MyPost a=this.posts.get(String.valueOf(id));
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
                String v=this.posts.get(p.getParentID()).getOwnerUser();
                v = this.users.get(v).getName();
                Pergunta ç= (Pergunta) d;
                String z= ç.getTitle();
                r =  new Pair(z,v);
             }
        }
        return r;
    }
    //query 2
    public List<Long> topMostActive(int N){
        List<Long> list;
        list=this.usersByNPosts.stream()
                .limit(N)
                .map(e->Long.valueOf(e.getId()))
                .collect(Collectors.toList());
        return list;
    }
    //query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
        int l1;
        int l2; 
        int j1;
        int j2;
        long resp = 0;
        long perg = 0;
        for(int i = 17-(end.getYear()-2000); i<= 17-(begin.getYear()-2000); i++){
            if(i == 17-(end.getYear()-2000)) j1 = end.getMonthValue(); else j1 = 12;
            if(i == 17-(begin.getYear()-2000)) j2 = begin.getMonthValue(); else j2 = 1;
            for(int a = 12-j1; a <= 12-j2; a++){
                if(i == 17-(end.getYear()-2000)) l1 = end.getDayOfMonth(); else l1  = 31;
                if(i == 17-(begin.getYear()-2000)) l2 = begin.getDayOfMonth(); else l2  = 1;
                for (int k = 31-l1; k<=31-l2; k++){
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
    //query 5
    public Pair<String, List<Long>> getUserInfo(long id){
        myUser c=users.get(String.valueOf(id));
        List m;
        m=c.getLastPosts().stream()
                          .map(MyPost::getID)
                          .collect(Collectors.toList());
        String k= c.getAboutMe();
        return new Pair (k,m);
    }
    //query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
        List t=new ArrayList <Long>();
        int l1;
        int l2;
        int j1;
        int j2;
        for(int i = 17-(end.getYear()-2000); i<= 17-(begin.getYear()-2000); i++){
            if(i == 17-(end.getYear()-2000)) j1 = end.getMonthValue(); else j1 = 12;
            if(i == 17-(begin.getYear()-2000)) j2 = begin.getMonthValue(); else j2 = 1;
            for(int a = 12-j1; a <= 12-j2; a++){
                if(i == 17-(end.getYear()-2000)) l1 = end.getDayOfMonth(); else l1  = 31;
                if(i == 17-(begin.getYear()-2000)) l2 = begin.getDayOfMonth(); else l2  = 1;
                for (int k = 31-l1; k<=31-l2; k++){
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

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        TreeSet<Resposta> res = new TreeSet<>(new ComparadorRespostasVotos());
        int l1;
        int l2;
        int j1;
        int j2;
        for(int i = 17-(end.getYear()-2000); i<= 17-(begin.getYear()-2000); i++) {
            if (i == 17-(end.getYear()-2000)) j1 = end.getMonthValue();
            else j1 = 12;
            if (i == 17 - (begin.getYear() - 2000)) j2 = begin.getMonthValue();
            else j2 = 1;
            for (int a = 12 - j1; a <= 12 - j2; a++) {
                if(i == 17-(end.getYear()-2000)) l1 = end.getDayOfMonth(); else l1  = 31;
                if(i == 17-(begin.getYear()-2000)) l2 = begin.getDayOfMonth(); else l2  = 1;
                for (int k = 31-l1; k<=31-l2; k++){
                    for (MyPost p : this.postsList.get(i).get(a).get(k)) {
                        if (p instanceof Resposta) {
                            Resposta r = (Resposta) p;
                            res.add(r.clone());
                        }

                    }
                }
            }
        }
        return res.stream().map(p -> Long.parseLong(p.getID())).limit(N).collect(Collectors.toList());
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        TreeSet<Pergunta> res= new TreeSet<>(new ComparadorPerguntasPorResposta());
        int l1;
        int l2;
        int j1;
        int j2;
        for(int i = 17-(end.getYear()-2000); i<= 17-(begin.getYear()-2000); i++) {
            if (i == 17-(end.getYear()-2000)) j1 = end.getMonthValue();
            else j1 = 12;
            if (i == 17 - (begin.getYear() - 2000)) j2 = begin.getMonthValue();
            else j2 = 1;
            for (int a = 12 - j1; a <= 12 - j2; a++) {
                if(i == 17-(end.getYear()-2000)) l1 = end.getDayOfMonth(); else l1  = 31;
                if(i == 17-(begin.getYear()-2000)) l2 = begin.getDayOfMonth(); else l2  = 1;
                for (int k = 31-l1; k<=31-l2; k++){
                    for (MyPost p : this.questionsList.get(i).get(a).get(k)) {
                        Pergunta v = (Pergunta) p;
                        res.add(v);

                    }
                }
            }
        }

        return res.stream().map(p -> Long.parseLong(p.getID())).limit(N).collect(Collectors.toList());
    }

    //query 8
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
    //query 9
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
    //query 10
    public long betterAnswer(long id){
        String x = String.valueOf(id);
        MyPost p = posts.get(x);
        if(p instanceof Pergunta){
            Pergunta y = (Pergunta) p;
            return y.getBestAnswer();
        }else
            return -1;
    }
    //query 11
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
            if(i == 17-(end.getYear()-2000)) j1 = end.getMonthValue(); else j1 = 12;
            if(i == 17-(begin.getYear()-2000)) j2 = begin.getMonthValue(); else j2 = 1;
            for(int a = 12-j1; a <= 12-j2; a++){
                if(i == 17-(end.getYear()-2000)) l1 = end.getDayOfMonth(); else l1  = 31;
                if(i == 17-(begin.getYear()-2000)) l2 = begin.getDayOfMonth(); else l2  = 1;
                for (int k = 31-l1; k<=31-l2; k++){
                    for(MyPost p : this.questionsList.get(i).get(a).get(k)){
                        Pergunta v= (Pergunta) p;
                        if (topN.containsKey(v.getOwnerUser())){
                            for(String s: v.getTags()) {
                                if(aux.containsKey(tags.get(s))){
                                    aux.replace(tags.get(s),aux.get(tags.get(s))+1);
                                }else aux.put(tags.get(s),1);
                            }
                        }
                    }
                }
            }
        }

              List<String> aux2 = aux.entrySet().stream()
                                        .sorted(new ComparadorTagsPorOcorrencia())
                                        .map(Map.Entry::getKey)
                                        .collect(Collectors.toList());
        for (int i = 0; i<N;i++)
            r.add(Long.parseLong(aux2.get(i)));

        return r;
    }

    /**
     * Função que permite limpar os conteudos da estrutura principal
     */
    public void clear(){
        users.clear();
        usersByNPosts.clear();
        usersByReputation.clear();
        posts.clear();
        postsList.clear();
        questionsList.clear();
        for(int i = 0; i<18; i++){
            this.postsList.add(new ArrayList<>());
            this.questionsList.add(new ArrayList<>());
            for(int i2 = 0; i2<12; i2++){
                this.postsList.get(i).add(new ArrayList<>());
                this.questionsList.get(i).add(new ArrayList<>());
                for(int i3 = 0; i3<31; i3++){
                    this.postsList.get(i).get(i2).add(new ArrayList<>());
                    this.questionsList.get(i).get(i2).add(new ArrayList<>());
                }
            }
        }
    }
}    
    

