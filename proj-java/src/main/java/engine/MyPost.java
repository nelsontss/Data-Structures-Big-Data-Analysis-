package engine;
import java.time.LocalDate;
import java.util.Iterator;
/**
 * Classe que implementa um post
 *
 * Grupo 48
 * 12/6/2018
 */
public abstract class MyPost
{
    // Variáveis da classe post
    private String id;
    private String ownerUser;
    private LocalDate data;
    

    /**
     * Construtor vazio da classe MyPost
     */
    public MyPost()
    {
        // initialise instance variables
        this.id ="";
        this.ownerUser="";
        this.data= LocalDate.now();
    }

    /**
     * Construtor parametrizado da classe MyPost
     * @param id ID do post
     * @param ou ID do proprietário do post
     * @param data Data do post
     */
    public MyPost(String id, String ou, LocalDate data)
    {
        this.id =id;
        this.ownerUser=ou;
        this.data= data;
    }

    /**
     * Construtor de cópia do post
     * @param mp Post que se pretende copiar
     */
    public MyPost(MyPost mp)
    {
        this.id =mp.getID();
        this.ownerUser=mp.getOwnerUser();
        this.data= mp.getData();
    }
    
    //gets & sets

    /**
     * Função que retorna o ID do post
     * @return ID do post
     */
    public String getID(){
        return this.id;
    }

    /**
     * Função que retorna o ID do proprietário do post
     * @return ID do proprietário do post
     */
    public String getOwnerUser(){
        return this.ownerUser;
    }

    /**
     * Função que retorna a data do post
     * @return Data do post
     */
    public LocalDate getData(){
        return this.data;
    }

    /**
     * Função que define o ID do post
     * @param id ID do post dado
     */
    public void setID(String id){
        this.id=id;
    }

    /**
     * Função que define o ID do proprietário do post
     * @param ou ID do proprietário do post dado
     */
    public void setOwnerUser(String ou){
        this.ownerUser=ou;
    }

    /**
     * Função que define a data do post
     * @param data Data do post dado
     */
    public void setData(LocalDate data){
        this.data=data;
    }

    /**
     * Função abstrata que devolve a cópia do post
     * @return Cópia do post
     */
    public abstract MyPost clone();

    /**
     * Função que averigua se um post e um objeto são iguais
     * @param o Objeto a comparar
     * @return True se são iguais, false se não são iguais
     */
    public boolean equals(Object o){
        if(this==o) return true;
        if(o==null && this.getClass()!=o.getClass()) return false;
        MyPost mp= (MyPost) o;
        return (this.id.equals(mp.getID()) && this.ownerUser.equals(mp.getOwnerUser())
        && this.data.equals(mp.getData()));
    }

    /**
     * Função que passa um post para uma String
     * @return String representativa do post
     */
    public String toString(){
        StringBuilder sb= new StringBuilder();
        sb.append("ID do post: ");sb.append(this.id);
        sb.append("ID do proprietario do post: ");sb.append(this.ownerUser);
        sb.append("Data do post: ");sb.append(this.data);
        return sb.toString();
    }
}
