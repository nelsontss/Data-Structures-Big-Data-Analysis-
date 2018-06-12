package engine;

import javax.swing.tree.TreeCellEditor;
import java.util.*;
import java.time.LocalDate;
/**
 * Classe que implementa uma pergunta
 *
 * @author Grupo 48
 * @version 12/6/2018
 */
public class Pergunta extends MyPost
{
    // Variáveis da classe pergunta
    private String title;
    private ArrayList<String> tags;
    private ArrayList<Resposta> resp;
    private HashMap<String,Resposta> respHash;
    private int answerCount;

    /**
     * Construtor vazio da classe pergunta
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

    /**
     * Construtor parametrizado da classe pergunta
     * @param title Título da pergunta
     * @param tags Lista de tags da pergunta
     * @param resp Lista de respostas da pergunta
     * @param respHash Tabela de hash com as respostas da pergunta
     * @param ac Numero de respostas à pergunta
     * @param id ID da pergunta
     * @param ownerUser ID do proprietário da pergunta
     * @param data Data da pergunta
     */
    public Pergunta(String title, ArrayList<String> tags, ArrayList<Resposta> resp, 
    HashMap<String,Resposta> respHash, int ac, String id, String ownerUser,LocalDate data)
    {
        super(id, ownerUser, data);
        this.title=title;
        setTags(tags);
        setResp(resp);
        setRespHash(respHash);
        this.answerCount=ac;
    }

    /**
     * Construtor de cópia da classe pergunta
     * @param p Pergunta que se pretende copiar
     */
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

    /**
     * Função que retorna o titulo da pergunta
     * @return Titulo da pergunta
     */
    public String getTitle(){
        return this.title;
    }

    /**
     * Função que retorna uma lista com as tags da pergunta
     * @return Lista de tags da pergunta
     */
    public ArrayList<String> getTags(){
        ArrayList<String> res = new ArrayList<String>();
        for(String s: this.tags)
            res.add(s);
        return res;
    }

    /**
     * Função que retorna a lista de respostas da pergunta
     * @return Lista de respostas da pergunta
     */
    public ArrayList<Resposta> getResp(){
        ArrayList<Resposta> res = new ArrayList<Resposta>();
        for(Resposta r: this.resp)
            res.add(r.clone());
        return res;
    }

    /**
     * Função que retorna a tabela de hash com as respostas da pergunta
     * @return Tabela de hash com as respostas da pergunta
     */
    public HashMap<String,Resposta> getRespHash(){
        HashMap<String,Resposta> res= new HashMap<String,Resposta>();
        for(Map.Entry<String,Resposta> sr: this.respHash.entrySet())
            res.put(sr.getKey(),sr.getValue().clone());
        return res;
    }

    /**
     * Função que retorna o número de respostas da pergunta
     * @return Número de respostas da pergunta
     */
    public int getAnswerCount(){
        return this.answerCount;
    }

    /**
     * Função que define a lista de tags da pergunta
     * @param tags Lista de tags dada
     */
    public void setTags(ArrayList<String> tags){
        this.tags= new ArrayList<String>();
        for(String s: tags){
            this.tags.add(s);
        }
    }

    /**
     * Função que define a tabela de hash de respostas da pergunta
     * @param respHash Tabela de hash dada
     */
    public void setRespHash(HashMap<String,Resposta> respHash){
        this.respHash= new HashMap<String,Resposta>();
        for(Map.Entry<String,Resposta> r: respHash.entrySet())
            this.respHash.put(r.getKey(), r.getValue().clone());
    }

    /**
     * Função que define a lista de respostas da pergunta
     * @param resp Lista de respostas dada
     */
    public void setResp(ArrayList<Resposta> resp){
        this.resp= new ArrayList<Resposta>();
        for(Resposta r: resp)
            this.resp.add(r.clone());
    }

    /**
     * Função que define o número de respostas da pergunta
     * @param ac Número de respostas dado
     */
    public void setAnswerCount(int ac){
        this.answerCount=ac;
    }

    /**
     * Função que adiciona uma resposta à lista e tabela de hash de respostas
     * @param r Resposta a adicionar
     */
    public void addResp(Resposta r){
        this.resp.add(r.clone());
        this.respHash.put(r.getID(),r.clone());
    }

    /**
     * Função que devolve a melhor resposta feita à pergunta
     * @return Resposta com melhor pontuação
     */
    public Long getBestAnswer(){
        TreeSet<Resposta> r = new TreeSet<>(new ComparadorRespostasPorPont());
        for(Resposta x : resp)
            r.add(x);

        return Long.parseLong(r.first().getID());
    }

    /**
     * Função que averigua se dois utilizadores participaram na resposta à pergunta
     * @param id1 Utilizador 1
     * @param id2 Utilizador 2
     * @return True se ambos participaram, false se pelo menos um não participou
     */
    public boolean bothParticipated(long id1, long id2){
        int flag = 0;
        if(id1==Long.valueOf(this.getOwnerUser()) && respHash.containsKey(String.valueOf(id2))){
            return true;
        }
        if(id2==Long.valueOf(this.getOwnerUser()) && respHash.containsKey(String.valueOf(id1))){
            return true;
        }
        if(respHash.containsKey(String.valueOf(id1)) && respHash.containsKey(String.valueOf(id2))){
            return true;
        }
        return false;

    }

    /**
     * Função que retorna uma cópia da pergunta
     * @return Cópia da pergunta
     */
    public Pergunta clone(){
        return new Pergunta(this);
    }

    /**
     * Função que averigua se uma pergunta e um objeto são iguais
     * @param o Objeto a comparar
     * @return True se forem iguais, false se não forem iguais
     */
    public boolean equals(Object o){
        if(this==o) return true;
        if(o==null && this.getClass()!=o.getClass()) return false;
        Pergunta p= (Pergunta) o;
        return super.equals(o) && this.title.equals(p.getTitle()) && this.tags.equals(p.getTags())
        && this.resp.equals(p.getResp()) && this.respHash.equals(p.getRespHash());
    }

    /**
     * Função que converte uma pergunta numa String
     * @return String representativa da pergunta
     */
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
