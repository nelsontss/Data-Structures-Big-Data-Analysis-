package engine;
import java.util.ArrayList;

/**
 * Classe que implementa um utilizador
 * @author Grupo 48
 * @version 12/06/2018
 */
public class myUser
{
    // variáveis de instância
    private String id;
    private String name;
    private String aboutme;
    private int questions;
    private int answers;
    private int totalposts;
    private int reputation;
    private ArrayList <MyPost> lastposts;

    /**
     * Construtor para objetos da classe myUser
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

    /**
     * Constructor parametrizado para a classe myUser
     * @param id Id do utilizador
     * @param name Nome do utilizador
     * @param aboutme About me do utilizador
     * @param questions Numero de perguntas feitas
     * @param answers Numero de respostas feitas
     * @param totalposts Numero total de posts feitos
     * @param reputation Reputação do utilizador
     * @param lastposts ultimos posts feitos pelo user
     */
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

    /**
     * Construtor de cópia da classe myUser
     * @param User
     */
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
    
    /**
     * Metodo que devolve o id do user
     * @return Id do user
     */
    public String getId(){
    return this.id;
    }
    
    /**
     * Metodo que devolve o nome do user
     * @return Nome do user
     */
    public String getName(){
    return this.name;
    }
    
    /**
     * Metodo que devolve o about me do user
     * @return About me do user
     */
    public String getAboutMe(){
    return this.aboutme;
    }
    
    /**
     * Metodo que devolve o numero de perguntas feitas pelo user
     * @return numero de perguntas feitas pelo user
     */
    public int getQuestions(){
    return this.questions;
    }
    
    /**
     * Metodo que devolve o numero de respostas feitas pelo user
     * @return numero de respostas feitas pelo user
     */
    public int getAnswers(){
    return this.answers;
    }
    
    /**
     * Metodo que devolve o numero de posts feitos pelo user
     * @return numero de posts feitos pelo user
     */
    public int getTotalPosts(){
    return this.totalposts;
    }
    
    /**
     * Metodo que devolve a reputação do user
     * @return reputação do user
     */
    public int getReputation(){
    return this.reputation;
    }
    
    /**
     * Metodo que devolve os ultimos posts feitos pelo user     
     * @return ultimos posts feitos pelo user        
     */
    public ArrayList<MyPost> getLastPosts(){
            ArrayList<MyPost> r = new ArrayList<MyPost>();
            
            for(MyPost s: this.lastposts){
                MyPost x = (MyPost) s;
                r.add(x.clone());
            }
            return r;
    }
    
    /**
     * Metodo que define o ID do user
     * @param id ID do user
     */
    public void setId(String id){

        this.id=id;
    }
    
    /**
     * Metodo que define o nome do user
     * @param Name Nome do user
     */
    public void setName(String Name){
    this.name=name;
    }

    /**
     * Metodo que define o about me do user
     * @param aboutme Informação "aboutme" do user
     */
    public void setAboutMe (String aboutme){
    this.aboutme=aboutme;
    }
    
    /**
     * Metodo que define a reputação do user
     * @param reputation Reputação do user
     */
    public void setReputation(int reputation){
    this.reputation=reputation;
    }
    
    /**
     * Metodo que define o numero de perguntas feitas pelo user
     * @param questions Numero de perguntas feitas pelo user
     */
    public void setQuestions(int questions){
    this.questions=questions;
    }
    
    /**
     * Metodo que define o numero de respostas feitas pelo user
     * @param answers Numero de respostas feitas pelo user
     */
    public void setAnswers(int answers){
    this.answers=answers;
    }
    
    /**
     * Metodo que define o numero total de posts feitos pelo user
     * @param totalposts Numero total de posts feitos pelo user
     */
    public void setTotalPosts(int totalposts){
    this.totalposts=totalposts;
    }
    
    /**
     * Metodo que define o array com os ultimos posts do user
     * @param lastposts Array com os ultimos posts do user
     */
    public void setLastPosts(ArrayList<MyPost> lastposts){
        this.lastposts=new ArrayList<MyPost>();
        for(MyPost s: lastposts)
                this.lastposts.add(s);
    }
    
    /**
     * Função que aumenta o numero de respostas , e consequentemente de posts do utilizador
     */ 
    public void aumentaAnswers(){
        this.answers++;
        this.totalposts++;
    }
    /**
     * Função que aumenta o numero de perguntas , e consequentemente de posts do utilizador
     */  
    public void aumentaQuestions(){
        this.questions++;
        this.totalposts++;
    }

    /**
     * Função que adiciona um post aos lastposts do user
     *@param p Post a adicionar
     */  
    public void addLastPost(MyPost p){
        if(this.lastposts.size()<10){
            this.lastposts.add(p);
        }else{
            if(this.lastposts.get(this.lastposts.size()-1).getData().compareTo(p.getData())<0){
                this.lastposts.set(this.lastposts.size()-1,p);
            }

        }
        this.lastposts.sort(new ComparadorPostsPorData());
    }
        
     /**
     * Função que clona o user
     *@return User clonado.
     */      
    public myUser clone() {
        return new myUser(this); 
    }
}
